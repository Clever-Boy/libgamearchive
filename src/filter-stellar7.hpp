/**
 * @file  filter-stellar7.hpp
 * @brief FilterType for Stellar 7 compression algorithm.
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

#ifndef _CAMOTO_FILTER_STELLAR7_HPP_
#define _CAMOTO_FILTER_STELLAR7_HPP_

#include <camoto/gamearchive/filtertype.hpp>

namespace camoto {
namespace gamearchive {

/// Stellar 7 decompression filter.
class FilterType_Stellar7: virtual public FilterType
{
	public:
		FilterType_Stellar7();
		virtual ~FilterType_Stellar7();

		virtual std::string code() const;
		virtual std::string friendlyName() const;
		virtual std::vector<std::string> games() const;
		virtual std::unique_ptr<stream::inout> apply(
			std::unique_ptr<stream::inout> target, stream::fn_notify_prefiltered_size resize)
			const;
		virtual std::unique_ptr<stream::input> apply(
			std::unique_ptr<stream::input> target) const;
		virtual std::unique_ptr<stream::output> apply(
			std::unique_ptr<stream::output> target, stream::fn_notify_prefiltered_size resize)
			const;
};

} // namespace gamearchive
} // namespace camoto

#endif // _CAMOTO_FILTER_STELLAR7_HPP_
