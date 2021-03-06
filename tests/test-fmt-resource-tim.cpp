/**
 * @file   test-fmt-resource-tim.cpp
 * @brief  Test code for The Incredible Machine resource archives.
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

#include "test-archive.hpp"

class test_suppfat_resource_tim: public test_archive
{
	public:
		test_suppfat_resource_tim()
		{
			this->type = "resource-tim.fat";
		}

		virtual std::string content_12()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
			);
		}

		virtual std::string content_1r2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
			);
		}

		virtual std::string content_123()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x40\x00\x00\x00"
			);
		}

		virtual std::string content_132()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x42\x00\x00\x00"
			);
		}

		virtual std::string content_1342()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x42\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x63\x00\x00\x00"
			);
		}

		virtual std::string content_2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
			);
		}

		virtual std::string content_0()
		{
			return STRING_WITH_NULLS(
				""
			);
		}

		virtual std::string content_32()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x22\x00\x00\x00"
			);
		}

		virtual std::string content_21()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x20\x00\x00\x00"
			);
		}

		virtual std::string content_1l2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x25\x00\x00\x00"
			);
		}

		virtual std::string content_1s2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x1b\x00\x00\x00"
			);
		}

		virtual std::string content_1w2()
		{
			return STRING_WITH_NULLS(
				"\x00\x00" "\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00" "\x00\x00" "\x28\x00\x00\x00"
			);
		}
};

class test_resource_tim: public test_archive
{
	public:
		test_resource_tim()
		{
			this->type = "resource-tim";
			this->lenMaxFilename = 12;
			this->suppResult[SuppItem::FAT] = std::make_unique<test_suppfat_resource_tim>();
		}

		void addTests()
		{
			this->test_archive::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->content_12());

			// c01: File too short
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00"
			));

			// c02: File too large
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x1f\x00\x00\x00" "This is one.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			));

			// c03: File truncated
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x1f\x00\x00\x00" "This is one.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00"
			));
		}

		virtual std::string content_12()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is one.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_1r2()
		{
			return STRING_WITH_NULLS(
				"THREE.DAT\0\0\0\0"   "\x0f\x00\x00\x00" "This is one.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_123()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is one.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
				"THREE.DAT\0\0\0\0"   "\x11\x00\x00\x00" "This is three.dat"
			);
		}

		virtual std::string content_132()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is one.dat"
				"THREE.DAT\0\0\0\0"   "\x11\x00\x00\x00" "This is three.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_1342()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is one.dat"
				"THREE.DAT\0\0\0\0"   "\x11\x00\x00\x00" "This is three.dat"
				"FOUR.DAT\0\0\0\0\0"  "\x10\x00\x00\x00" "This is four.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_2()
		{
			return STRING_WITH_NULLS(
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_0()
		{
			return STRING_WITH_NULLS(
				""
			);
		}

		virtual std::string content_32()
		{
			return STRING_WITH_NULLS(
				"THREE.DAT\0\0\0\0"   "\x11\x00\x00\x00" "This is three.dat"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_21()
		{
			return STRING_WITH_NULLS(
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
				"ONE.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is one.dat"
			);
		}

		virtual std::string content_1l2()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x14\x00\x00\x00" "This is one.dat\0\0\0\0\0"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_1s2()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x0a\x00\x00\x00" "This is on"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}

		virtual std::string content_1w2()
		{
			return STRING_WITH_NULLS(
				"ONE.DAT\0\0\0\0\0\0" "\x17\x00\x00\x00" "Now resized to 23 chars"
				"TWO.DAT\0\0\0\0\0\0" "\x0f\x00\x00\x00" "This is two.dat"
			);
		}
};

IMPLEMENT_TESTS(resource_tim);
