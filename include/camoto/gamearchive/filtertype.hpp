/**
 * @file   filtertype.hpp
 * @brief  Declaration of top-level FilterType class, for performing certain
 *         processing operations on data streams (compression/decompression,
 *         encryption, etc.)
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

#ifndef _CAMOTO_GAMEARCHIVE_FILTERTYPE_HPP_
#define _CAMOTO_GAMEARCHIVE_FILTERTYPE_HPP_

#include <boost/shared_ptr.hpp>
#include <exception>
#include <iostream>
#include <sstream>
#include <vector>

#include <camoto/types.hpp>
#include <camoto/exceptions.hpp>
#include <camoto/gamearchive/archivetype.hpp> // for supp types

namespace camoto {
namespace gamearchive {

/// Primary interface to a filter.
/**
 * This class represents a filter.  Its functions are used to manipulate C++
 * iostreams so that the data passing through the stream is altered in some
 * way, such as by being compressed or decompressed.
 */
class FilterType {

	public:

		/// Get a short code to identify this filter, e.g. "cmp-zone66"
		/**
		 * This can be useful for command-line arguments.
		 *
		 * @return The filter's short name/ID.
		 */
		virtual std::string getFilterCode() const
			throw () = 0;

		/// Get the filter name, e.g. "Zone 66 compression"
		/**
		 * @return The filter name.
		 */
		virtual std::string getFriendlyName() const
			throw () = 0;

		/// Get a list of games using this format.
		/**
		 * @return A vector of game names, such as "Zone 66".
		 */
		virtual std::vector<std::string> getGameList() const
			throw () = 0;

		/// Apply the algorithm to an iostream.
		/**
		 * This function takes in a target iostream and applies the algorithm to
		 * it.  The target stream can be empty.
		 *
		 * Any data written to the returned stream will have the algorithm applied
		 * (e.g. data is compressed) and then written to the target stream.
		 *
		 * Any data read from the returned stream will read data from the target
		 * stream and apply the algorithm in reverse (e.g. data is decompressed.)
		 *
		 * @param target
		 *   Target stream where the filtered data exists or is to end up.
		 *
		 * @param fnTruncate
		 *   Callback to set the size of the target stream on flush().
		 *
		 * @return Clear/plaintext stream providing data from target after
		 *   processing.
		 */
		virtual iostream_sptr apply(iostream_sptr target, FN_TRUNCATE fnTruncate)
			throw (ECorruptedData) = 0;

		/// Apply the algorithm to an istream.
		/**
		 * @sa apply(iostream_sptr, FN_TRUNCATE)
		 */
		virtual istream_sptr apply(istream_sptr target)
			throw (ECorruptedData) = 0;

		/// Apply the algorithm to an ostream.
		/**
		 * @sa apply(iostream_sptr, FN_TRUNCATE)
		 */
		virtual ostream_sptr apply(ostream_sptr target, FN_TRUNCATE fnTruncate)
			throw (ECorruptedData) = 0;

};

/// Shared pointer to an FilterType.
typedef boost::shared_ptr<FilterType> FilterTypePtr;

/// Vector of FilterType shared pointers.
typedef std::vector<FilterTypePtr> VC_FILTERTYPE;

} // namespace gamearchive
} // namespace camoto

#endif // _CAMOTO_GAMEARCHIVE_FILTERTYPE_HPP_