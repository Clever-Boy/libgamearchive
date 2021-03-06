/**
 * @file  stream_archfile.cpp
 * @brief Provide a stream that accesses a file within an Archive instance.
 *
 * Copyright (C) 2010-2016 Adam Nielsen <malvineous@shikadi.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <camoto/util.hpp>
#include <camoto/gamearchive/manager.hpp>
#include <camoto/gamearchive/stream_archfile.hpp>

namespace camoto {
namespace gamearchive {

std::unique_ptr<stream::inout> applyFilter(std::unique_ptr<archfile> s,
	const std::string& filter)
{
	if (filter.empty()) return std::move(s);

	// The file needs to be filtered first
	auto pFilterType = FilterManager::byCode(filter);
	if (!pFilterType) {
		throw stream::error(createString(
			"could not find filter \"" << filter << "\""
		));
	}

	return pFilterType->apply(
		std::unique_ptr<stream::inout>(std::move(s)),
		[](stream::output_filtered* filt, stream::len newRealSize) {
			archfile* arch = nullptr;
			while (filt) {
				auto filt_content = filt->get_stream().get();
				arch = dynamic_cast<archfile*>(filt_content);
				if (arch) break;

				// This isn't an archfile, so see if this is a layered filter and
				// there's another one below it.
				filt = dynamic_cast<stream::output_filtered*>(filt_content);
			}
			// If this fails, the underlying stream (even if it's buried under layers
			// of output_filtered streams) isn't an archfile.
			assert(arch);

			if (arch) arch->setRealSize(newRealSize);
			return;
		}
	);
}

archfile_core::archfile_core(const Archive::FileHandle& id)
	:	sub_core(0, 0),
		id(const_cast<Archive::FileHandle&>(id)),
		fat(Archive_FAT::FATEntry::cast(id)),
		fatFixed(FixedArchive::FixedEntry::cast(id))
{
}

void archfile_core::relocate(stream::delta off)
{
	throw stream::error("archfile_core::relocate() should never be called");
}

void archfile_core::resize(stream::len len)
{
	throw stream::error("archfile_core::resize() should never be called");
}

stream::pos archfile_core::sub_start() const
{
	if (this->fat) {
		if (!this->fat->bValid) {
			throw stream::error("Attempt to access closed or deleted file.");
		}
		return this->fat->iOffset + this->fat->lenHeader;
	} else if (this->fatFixed) {
		return this->fatFixed->fixed->offset;
	}
	throw stream::error("Unknown subfile type (not FATEntry or FixedEntry).");
}

stream::len archfile_core::sub_size() const
{
	if (this->fat) {
		if (!this->fat->bValid) {
			throw stream::error("Attempt to access closed or deleted file.");
		}
		return this->fat->storedSize;
	} else if (this->fatFixed) {
		return this->fatFixed->fixed->size;
	}
	throw stream::error("Unknown subfile type (not FATEntry or FixedEntry).");
}


input_archfile::input_archfile(const Archive::FileHandle& id,
	std::shared_ptr<stream::input> content)
	:	sub_core(0, 0), // length values are unused as we will be overriding them
		input_sub(content, 0, 0),
		archfile_core(id)
{
}


output_archfile::output_archfile(std::shared_ptr<Archive> archive,
	Archive::FileHandle id, std::shared_ptr<stream::output> content)
	:	sub_core(0, 0), // length values are unused as we will be overriding them
		output_sub(content, 0, 0, stream::fn_truncate_sub()),
		archfile_core(id),
		archive(archive)
{
}

void output_archfile::truncate(stream::len size)
{
	if (this->sub_size() == size) return; // nothing to do
	assert(this->id);

	stream::len newRealSize;
	if (this->id->fAttr & Archive::File::Attribute::Compressed) {
		// We're compressed, so the real and stored sizes are both valid
		newRealSize = this->id->realSize;
	} else {
		// We're not compressed, so the real size won't be updated by a filter,
		// so we need to update it here.
		newRealSize = size;
	}

	// Resize the file in the archive.  This function will also tell the
	// substream it can now write to a larger area.
	// We are updating both the stored (in-archive) and the real (extracted)
	// sizes, to handle the case where no filters are used and the sizes are
	// the same.  When filters are in use, the flush() function that writes
	// the filtered data out should call us first, then call the archive's
	// resize() function with the correct real/extracted size.
	this->archive->resize(this->id, size, newRealSize);

	// After a truncate the file pointer is always left at the new EOF
	try {
		this->seekp(size, stream::start);
	} catch (const stream::seek_error& e) {
		throw stream::write_error("Archive resize function silently failed!  "
			"Unable to seek to EOF after truncate: " + e.get_message());
	}
	return;
}

void output_archfile::setRealSize(stream::len newRealSize)
{
	this->archive->resize(this->id, this->id->storedSize, newRealSize);
	return;
}

void output_archfile::flush()
{
	// Don't flush the parent stream here because it's shared with the archive,
	// and we'll end up double-flushing which is bad if the archive is based on
	// a filtered stream.
	//this->out_parent->flush();

	if (this->archive.unique()) {
		// We are the only user of the shared archive, so the caller has no other
		// means to flush it.  So we will have to flush it for them.
		this->archive->flush();
	}
	return;
}


archfile::archfile(std::shared_ptr<Archive> archive, Archive::FileHandle id,
	std::shared_ptr<stream::inout> content)
	:	sub_core(0, 0),
		input_sub(content, 0, 0),
		output_sub(content, 0, 0, stream::fn_truncate_sub()),
		sub(content, 0, 0, stream::fn_truncate_sub()),
		archfile_core(id),
		input_archfile(id, content),
		output_archfile(archive, id, content)
{
}

} // namespace gamearchive
} // namespace camoto
