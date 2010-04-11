/*
 * main.cpp - Entry points for libgamearchive.
 *
 * Copyright (C) 2010 Adam Nielsen <malvineous@shikadi.net>
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

#include <string>
#include <camoto/gamearchive.hpp>

// Include all the file formats for the Manager to load
#include "fmt-grp-duke3d.hpp"
#include "fmt-vol-cosmo.hpp"
#include "debug.hpp"

namespace camoto {
namespace gamearchive {

#ifdef DEBUG
static bool registered_exit_func = false;
void exitFunc()
{
	std::cerr << "\e[44m --- Instance counts --- \e[49m\n";
	refcount_dump(GRPType);
	refcount_dump(GRPArchive);
	refcount_dump(FATArchive);
	refcount_dump(FATEntry);
	refcount_dump(substream_device);
	refcount_dump(segmented_stream_device);
}
#endif

Manager *getManager()
	throw ()
{
	return new Manager();
}

Manager::Manager()
	throw ()
{
#ifdef DEBUG
	if (!registered_exit_func) {
		atexit(exitFunc);
		registered_exit_func = true;
	}
#endif
	this->vcTypes.push_back(arch_sptr(new GRPType()));
	this->vcTypes.push_back(arch_sptr(new VOLType()));
}

Manager::~Manager()
	throw ()
{
}

Manager::arch_sptr Manager::getArchiveType(int iIndex)
	throw ()
{
	if (iIndex >= this->vcTypes.size()) return arch_sptr();
	return this->vcTypes[iIndex];
}

Manager::arch_sptr Manager::getArchiveTypeByCode(const std::string& strCode)
	throw ()
{
	for (VC_TYPES::const_iterator i = this->vcTypes.begin(); i != this->vcTypes.end(); i++) {
		if ((*i)->getArchiveCode().compare(strCode) == 0) return *i;
	}
	return arch_sptr();
}

} // namespace gamearchive
} // namespace camoto
