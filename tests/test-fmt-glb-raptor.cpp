/**
 * @file   test-fmt-glb-raptor.cpp
 * @brief  Test code for Raptor .GLB archives.
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

class test_glb_raptor: public test_archive
{
	public:
		test_glb_raptor()
		{
			this->type = "glb-raptor";
			this->lenMaxFilename = 15;
		}

		void addTests()
		{
			this->test_archive::addTests();

			// c00: Initial state
			this->isInstance(ArchiveType::Certainty::DefinitelyYes, this->content_12());

			// c01: Wrong signature bytes
			this->isInstance(ArchiveType::Certainty::DefinitelyNo, STRING_WITH_NULLS(
				"\x65\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa6\xdd\x13\x4b\xe1\x7b\x02\x63\xd9\x51\xdb\x13\x5a\xa6\xe8\x1b\x4d\x84\xba\xf2"
				"\x64\x9b\xd1\x09\x50\xff\x41\x74\xa6\xec\x22\x5a\xa1\x41\xda\x5c\xbc\x37\xae\x3a\x81\xcd\x0f\x42\x74\xab\xe1\x19"
				"This is one.dat"
				"This is two.dat"
			));
		}

		virtual std::string content_12()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x0f\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x63\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa6\xdd\x13\x4b\xe1\x7b\x02\x63\xd9\x51\xdb\x13\x5a\xa6\xe8\x1b\x4d\x84\xba\xf2"
				"\x64\x9b\xd1\x09\xb3\xff\x41\x74\xb5\xec\x22\x5a\xf5\x98\x29\x8a\x00\x78\x02\x3a\x81\xcd\x0f\x42\x74\xab\xe1\x19"
				"This is one.dat"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_1r2()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x0f\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x63\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa6\xdd\x13\x4b\xe6\x7a\x0e\x86\xfd\x62\xdc\x55\xf0\x3c\x7e\xb1\xe3\x1a\x50\x88"
				"\x64\x9b\xd1\x09\xb3\xff\x41\x74\xb5\xec\x22\x5a\xf5\x98\x29\x8a\x00\x78\x02\x3a\x81\xcd\x0f\x42\x74\xab\xe1\x19"
				"This is one.dat"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_123()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x03\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x70\x00\x00\x00" "\x0f\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x7f\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x8e\x00\x00\x00" "\x11\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat"
				"This is two.dat"
				"This is three.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x53\x9f\xe1\x14\x46\x7d\xb3\xeb\x32\x7e\xc0\xf3\x25\x5c\x92\xca\x11\x5d\x9f\xd2\x04\x3b\x71\xa9"
				"\x64\x9b\xd1\x09\xc0\x0c\x4e\x81\xc2\xf9\x2f\x67\xfd\x97\x1e\x7f\xf5\x6d\xf7\x2f\x76\xc2\x04\x37\x69\xa0\xd6\x0e"
				"\x64\x9b\xd1\x09\xcf\x1b\x5d\x90\xd1\x08\x3e\x76\x11\xb4\x45\xa6\x1c\x94\x1e\x56\x9d\xe9\x2b\x5e\x90\xc7\xfd\x35"
				"\x64\x9b\xd1\x09\xde\x2a\x6c\x9f\xe2\x19\x4f\x87\x22\xb6\x4a\xc2\x39\x9e\x18\x91\x2c\x78\xba\xed\x1f\x56\x8c\xc4"
				"This is one.dat"
				"This is two.dat"
				"This is three.dat"
			);
#endif
		}

		virtual std::string content_132()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x03\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x70\x00\x00\x00" "\x0f\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x7f\x00\x00\x00" "\x11\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x90\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat"
				"This is three.dat"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x53\x9f\xe1\x14\x46\x7d\xb3\xeb\x32\x7e\xc0\xf3\x25\x5c\x92\xca\x11\x5d\x9f\xd2\x04\x3b\x71\xa9"
				"\x64\x9b\xd1\x09\xc0\x0c\x4e\x81\xc2\xf9\x2f\x67\xfd\x97\x1e\x7f\xf5\x6d\xf7\x2f\x76\xc2\x04\x37\x69\xa0\xd6\x0e"
				"\x64\x9b\xd1\x09\xcf\x1b\x5d\x90\xd3\x0a\x40\x78\x13\xa7\x3b\xb3\x2a\x8f\x09\x82\x1d\x69\xab\xde\x10\x47\x7d\xb5"
				"\x64\x9b\xd1\x09\xe0\x2c\x6e\xa1\xe2\x19\x4f\x87\x22\xc5\x56\xb7\x2d\xa5\x2f\x67\xae\xfa\x3c\x6f\xa1\xd8\x0e\x46"
				"This is one.dat"
				"This is three.dat"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_1342()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x04\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x8C\x00\x00\x00" "\x0f\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x9B\x00\x00\x00" "\x11\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\xAC\x00\x00\x00" "\x10\x00\x00\x00" "FOUR.DAT\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\xBC\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat"
				"This is three.dat"
				"This is four.dat"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x54\xa0\xe2\x15\x47\x7e\xb4\xec\x33\x7f\xc1\xf4\x26\x5d\x93\xcb\x12\x5e\xa0\xd3\x05\x3c\x72\xaa"
				"\x64\x9b\xd1\x09\xdc\x28\x6a\x9d\xde\x15\x4b\x83\x19\xb3\x3a\x9b\x11\x89\x13\x4b\x92\xde\x20\x53\x85\xbc\xf2\x2a"
				"\x64\x9b\xd1\x09\xeb\x37\x79\xac\xef\x26\x5c\x94\x2f\xc3\x57\xcf\x46\xab\x25\x9e\x39\x85\xc7\xfa\x2c\x63\x99\xd1"
				"\x64\x9b\xd1\x09\xfc\x48\x8a\xbd\xff\x36\x6c\xa4\x31\xcc\x63\xe8\x48\xc3\x3a\xc6\x0d\x59\x9b\xce\x00\x37\x6d\xa5"
				"\x64\x9b\xd1\x09\x0c\x58\x9a\xcd\x0e\x45\x7b\xb3\x4e\xf1\x82\xe3\x59\xd1\x5b\x93\xda\x26\x68\x9b\xcd\x04\x3a\x72"
				"This is one.dat"
				"This is three.dat"
				"This is four.dat"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_2()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x01\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x38\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x51\x9d\xdf\x12\x44\x7b\xb1\xe9\x30\x7c\xbe\xf1\x23\x5a\x90\xc8\x0f\x5b\x9d\xd0\x02\x39\x6f\xa7"
				"\x64\x9b\xd1\x09\x88\xd4\x16\x49\x8a\xc1\xf7\x2f\xca\x6d\xfe\x5f\xd5\x4d\xd7\x0f\x56\xa2\xe4\x17\x49\x80\xb6\xee"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_0()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9B\xD1\x09\x50\x9C\xDE\x11\x43\x7A\xB0\xE8\x2F\x7B\xBD\xF0\x22\x59\x8F\xC7\x0E\x5A\x9C\xCF\x01\x38\x6E\xA6"
			);
#endif
		}

		virtual std::string content_32()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x11\x00\x00\x00" "THREE.DAT\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x65\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is three.dat"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa8\xdf\x15\x4d\xe8\x7c\x10\x88\xff\x64\xde\x57\xf2\x3e\x80\xb3\xe5\x1c\x52\x8a"
				"\x64\x9b\xd1\x09\xb5\x01\x43\x76\xb7\xee\x24\x5c\xf7\x9a\x2b\x8c\x02\x7a\x04\x3c\x83\xcf\x11\x44\x76\xad\xe3\x1b"
				"This is three.dat"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_21()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x63\x00\x00\x00" "\x0f\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is two.dat"
				"This is one.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa6\xdd\x13\x4b\xe6\x89\x1a\x7b\xf1\x69\xf3\x2b\x72\xbe\x00\x33\x65\x9c\xd2\x0a"
				"\x64\x9b\xd1\x09\xb3\xff\x41\x74\xb5\xec\x22\x5a\xf0\x8a\x11\x72\xe8\x60\xea\x22\x69\xb5\xf7\x2a\x5c\x93\xc9\x01"
				"This is two.dat"
				"This is one.dat"
			);
#endif
		}

		virtual std::string content_1l2()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x14\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x68\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is one.dat\0\0\0\0\0"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xab\xe2\x18\x50\xe6\x80\x07\x68\xde\x56\xe0\x18\x5f\xab\xed\x20\x52\x89\xbf\xf7"
				"\x64\x9b\xd1\x09\xb8\x04\x46\x79\xba\xf1\x27\x5f\xfa\x9d\x2e\x8f\x05\x7d\x07\x3f\x86\xd2\x14\x47\x79\xb0\xe6\x1e"
				"This is one.dat\0\0\0\0\0"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_1s2()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x0a\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x5e\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"This is on"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xa1\xd8\x0e\x46\xdc\x76\xfd\x5e\xd4\x4c\xd6\x0e\x55\xa1\xe3\x16\x48\x7f\xb5\xed"
				"\x64\x9b\xd1\x09\xae\xfa\x3c\x6f\xb0\xe7\x1d\x55\xf0\x93\x24\x85\xfb\x73\xfd\x35\x7c\xc8\x0a\x3d\x6f\xa6\xdc\x14"
				"This is on"
				"This is two.dat"
			);
#endif
		}

		virtual std::string content_1w2()
		{
#ifdef GLB_CLEARTEXT
			return STRING_WITH_NULLS(
				"\x00\x00\x00\x00" "\x02\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x54\x00\x00\x00" "\x17\x00\x00\x00" "ONE.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"\x00\x00\x00\x00" "\x6B\x00\x00\x00" "\x0f\x00\x00\x00" "TWO.DAT\x00\x00\x00\x00\x00" "\x00\x00\x00\x00"
				"Now resized to 23 chars"
				"This is two.dat"
			);
#else
			return STRING_WITH_NULLS(
				"\x64\x9b\xd1\x09\x52\x9e\xe0\x13\x45\x7c\xb2\xea\x31\x7d\xbf\xf2\x24\x5b\x91\xc9\x10\x5c\x9e\xd1\x03\x3a\x70\xa8"
				"\x64\x9b\xd1\x09\xa4\xf0\x32\x65\xae\xe5\x1b\x53\xe9\x83\x0a\x6b\xe1\x59\xe3\x1b\x62\xae\xf0\x23\x55\x8c\xc2\xfa"
				"\x64\x9b\xd1\x09\xbb\x07\x49\x7c\xbd\xf4\x2a\x62\xfd\xa0\x31\x92\x08\x80\x0a\x42\x89\xd5\x17\x4a\x7c\xb3\xe9\x21"
				"Now resized to 23 chars"
				"This is two.dat"
			);
#endif
		}
};

IMPLEMENT_TESTS(glb_raptor);
