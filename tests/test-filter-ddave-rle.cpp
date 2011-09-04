/**
 * @file   test-filter-ddave-rle.cpp
 * @brief  Test code for Dangerous Dave RLE algorithm.
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

#include <boost/test/unit_test.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <iostream>
#include <sstream>
#include <camoto/util.hpp>

#include "tests.hpp"
#include "../src/filter-ddave-rle.hpp"

using namespace camoto;
using namespace camoto::gamearchive;
namespace io = boost::iostreams;

struct ddave_rle_sample: public default_sample {

	std::stringstream *out;
	ostream_sptr out_s;
	DDaveRLEFilterType filt;

	ddave_rle_sample() :
		out(new std::stringstream),
		out_s(out)
	{
	}

	boost::test_tools::predicate_result is_equal(const std::string& strExpected)
	{
		// See if the stringstream now matches what we expected
		return this->default_sample::is_equal(strExpected, out->str());
	}

};

void dummyTrunc(int len)
{
	return;
}

#define DATA_ENCODED \
	"\x80\xAA\x00\x00\x81\xBB\xCC\x01\xDD" \
	"\x7F\x11" \
	"\x7E\x12" \
	"\xFE" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31" \
	"\x03\x44" \
	"\xFF" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22"

// Should have no effect on the decoded data when following DATA_ENCODED
#define DATA_BAD_TRAIL "\x00"

#define DATA_DECODED \
	"\xAA\x00\x00\x00\xBB\xCC\xDD\xDD\xDD\xDD" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11\x11\x11\x11\x11\x11\x11" \
	"\x11\x11" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12\x12\x12\x12\x12\x12\x12\x12" \
	"\x12" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31\x32" \
	"\x31\x32\x31\x32\x31\x32\x31" \
	"\x44\x44\x44\x44\x44\x44" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22" \
	"\x21\x22\x21\x22\x21\x22\x21\x22"

BOOST_FIXTURE_TEST_SUITE(ddave_rle_suite, ddave_rle_sample)

BOOST_AUTO_TEST_CASE(decode)
{
	BOOST_TEST_MESSAGE("Un-RLE some data");

	std::stringstream *pss = new std::stringstream;
	iostream_sptr in(pss);
	*in << makeString(DATA_ENCODED);

	istream_sptr inf = this->filt.apply(in);
	inf = this->filt.apply(in);

	boost::iostreams::copy(*inf, *out);

	out->flush();

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_DECODED)),
		"Decoding RLE data failed");
}

BOOST_AUTO_TEST_CASE(decoderw)
{
	BOOST_TEST_MESSAGE("Un-RLE some data to a r/w stream, with trailing garbage");

	std::stringstream *pss = new std::stringstream;
	iostream_sptr in(pss);
	*in << makeString(DATA_ENCODED DATA_BAD_TRAIL);

	{
		DDaveRLEFilterType filt2;
		FN_TRUNCATE fnTrunc = boost::bind<void>(stringStreamTruncate, pss, _1);
		in = filt2.apply(in, NULL);

		boost::iostreams::copy(*in, *out);

		out->flush();
	}

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_DECODED)),
		"Decoding RLE data failed");

	BOOST_CHECK_MESSAGE(this->default_sample::is_equal(makeString(DATA_ENCODED
		DATA_BAD_TRAIL), pss->str()),
		"Decoding RLE data corrupted the source data");
}


BOOST_AUTO_TEST_CASE(encode)
{
	BOOST_TEST_MESSAGE("RLE some data");

	ostream_sptr inf = this->filt.apply(out_s, dummyTrunc);

	*inf << makeString(DATA_DECODED);

	flush(inf);

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_ENCODED)),
		"Encoding RLE data failed");
}

BOOST_AUTO_TEST_CASE(encode_repeat)
{
	BOOST_TEST_MESSAGE("RLE some data ending with repeated bytes");

	ostream_sptr inf = this->filt.apply(out_s, dummyTrunc);

	*inf << makeString(DATA_DECODED "\x45\x45");

	flush(inf);

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_ENCODED "\x81\x45\x45")),
		"Encoding RLE data failed");
}

BOOST_AUTO_TEST_CASE(encode_repeat_many)
{
	BOOST_TEST_MESSAGE("RLE some data ending with many repeated bytes");

	ostream_sptr inf = this->filt.apply(out_s, dummyTrunc);

	*inf << makeString(DATA_DECODED "\x45\x45\x45\x45\x45");

	flush(inf);

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_ENCODED "\x02\x45")),
		"Encoding RLE data failed");
}

BOOST_AUTO_TEST_CASE(encode_repeat_exact)
{
	BOOST_TEST_MESSAGE("RLE some data ending with three repeated bytes");

	ostream_sptr inf = this->filt.apply(out_s, dummyTrunc);

	*inf << makeString(DATA_DECODED "\x00\x00\x00\xFF\xFF\xFF");

	flush(inf);

	BOOST_CHECK_MESSAGE(is_equal(makeString(DATA_ENCODED "\x00\x00\x00\xFF")),
		"Encoding RLE data failed");
}

BOOST_AUTO_TEST_SUITE_END()