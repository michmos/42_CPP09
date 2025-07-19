
#include "../../inc/BtcConverter.hpp"
#include <gtest/gtest.h>

// all these tests assume the given csv file - if you change the csv file the tests will fail
TEST(BtcConverter, subjectTests) {
	BtcConverter converter("ex00/data.csv");
	EXPECT_FLOAT_EQ(converter.getValue("2011-01-03", 3).value(), 0.9);
	EXPECT_FLOAT_EQ(converter.getValue("2011-01-03", 2).value(), 0.6);
	EXPECT_FLOAT_EQ(converter.getValue("2011-01-03", 1).value(), 0.3);
	EXPECT_FLOAT_EQ(converter.getValue("2011-01-03", 1.2).value(), 0.36);
	EXPECT_FLOAT_EQ(converter.getValue("2011-01-09", 1).value(), 0.32);
	EXPECT_FLOAT_EQ(converter.getValue("2012-01-11", 1).value(), 7.1);
}


