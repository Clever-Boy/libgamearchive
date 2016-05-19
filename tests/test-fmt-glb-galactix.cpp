/**
 * @file   test-fmt-glb-galactix.cpp
 * @brief  Test code for Galactix .GLB archives.
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

// Uncomment to temporarily disable FAT encryption (for debugging)
//#define GLB_CLEARTEXT

#include "test-archive.hpp"

class test_glb_galactix: public test_archive
{
	public:
		test_glb_galactix()
		{
			this->type = "glb-galactix";
			this->lenMaxFilename = 21;
		}

		void addTests()
		{
			this->test_archive::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->content_12());

			// c01: Wrong signature bytes
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "XLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x63\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat"
				"This is two.dat"
			));
		}

		virtual std::string content_12()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x63\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat"
				"This is two.dat"
			);
		}

		virtual std::string content_1r2()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x63\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat"
				"This is two.dat"
			);
		}

		virtual std::string content_123()
		{
			return STRING_WITH_NULLS(
				"\x03\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x70\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x7f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x8e\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x11\x00"
				"This is one.dat"
				"This is two.dat"
				"This is three.dat"
			);
		}

		virtual std::string content_132()
		{
			return STRING_WITH_NULLS(
				"\x03\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x70\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x7f\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x11\x00"
				"\x90\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat"
				"This is three.dat"
				"This is two.dat"
			);
		}

		virtual std::string content_1342()
		{
			return STRING_WITH_NULLS(
				"\x04\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x8C\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x9B\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x11\x00"
				"\xAC\x00\x00\x00" "FOUR.DAT\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x10\x00"
				"\xBC\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat"
				"This is three.dat"
				"This is four.dat"
				"This is two.dat"
			);
		}

		virtual std::string content_2()
		{
			return STRING_WITH_NULLS(
				"\x01\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x38\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is two.dat"
			);
		}

		virtual std::string content_0()
		{
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
			);
		}

		virtual std::string content_32()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x11\x00"
				"\x65\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is three.dat"
				"This is two.dat"
			);
		}

		virtual std::string content_21()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"\x63\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is two.dat"
				"This is one.dat"
			);
		}

		virtual std::string content_1l2()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x14\x00"
				"\x68\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is one.dat\0\0\0\0\0"
				"This is two.dat"
			);
		}

		virtual std::string content_1s2()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0a\x00"
				"\x5e\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"This is on"
				"This is two.dat"
			);
		}

		virtual std::string content_1w2()
		{
			return STRING_WITH_NULLS(
				"\x02\x00\x00\x00" "GLIB FILE\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00"
				"\x54\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x17\x00"
				"\x6B\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x0f\x00"
				"Now resized to 23 chars"
				"This is two.dat"
			);
		}
};

IMPLEMENT_TESTS(glb_galactix);
