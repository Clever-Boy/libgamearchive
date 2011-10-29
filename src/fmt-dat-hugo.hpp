/**
 * @file   fmt-dat-hugo.cpp
 * @brief  Implementation of Hugo scenery .DAT file reader/writer.
 *
 * Copyright (C) 2010-2011 Adam Nielsen <malvineous@shikadi.net>
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

#ifndef _CAMOTO_FMT_DAT_HUGO_HPP_
#define _CAMOTO_FMT_DAT_HUGO_HPP_

#include <camoto/gamearchive.hpp>

#include "fatarchive.hpp"

namespace camoto {
namespace gamearchive {

class DAT_HugoType: virtual public ArchiveType {

	public:

		DAT_HugoType()
			throw ();

		virtual ~DAT_HugoType()
			throw ();

		virtual std::string getArchiveCode() const
			throw ();

		virtual std::string getFriendlyName() const
			throw ();

		virtual std::vector<std::string> getFileExtensions() const
			throw ();

		virtual std::vector<std::string> getGameList() const
			throw ();

		virtual ArchiveType::Certainty isInstance(stream::inout_sptr fsArchive) const
			throw (stream::error);

		virtual ArchivePtr newArchive(stream::inout_sptr psArchive, SuppData& suppData) const
			throw (stream::error);

		virtual ArchivePtr open(stream::inout_sptr fsArchive, SuppData& suppData) const
			throw (stream::error);

		virtual SuppFilenames getRequiredSupps(stream::input_sptr data,
			const std::string& filenameArchive) const
			throw ();

};

class DAT_HugoArchive: virtual public FATArchive {
	protected:

		stream::seg_sptr psFAT;
		struct DAT_HugoEntry: virtual public FATEntry {
			int file;
		};

	public:
		DAT_HugoArchive(stream::inout_sptr psArchive, stream::inout_sptr psFAT)
			throw (stream::error);

		virtual ~DAT_HugoArchive()
			throw ();

		// As per FATArchive (see there for docs)

		virtual void updateFileName(const FATEntry *pid, const std::string& strNewName)
			throw (stream::error);

		virtual void updateFileOffset(const FATEntry *pid, stream::delta offDelta)
			throw (stream::error);

		virtual void updateFileSize(const FATEntry *pid, stream::delta sizeDelta)
			throw (stream::error);

		virtual FATEntry *preInsertFile(const FATEntry *idBeforeThis, FATEntry *pNewEntry)
			throw (stream::error);

		virtual void preRemoveFile(const FATEntry *pid)
			throw (stream::error);

		virtual FATEntry *createNewFATEntry()
			throw ();

};

} // namespace gamearchive
} // namespace camoto

#endif // _CAMOTO_FMT_DAT_HUGO_HPP_
