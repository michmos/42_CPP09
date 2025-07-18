
#include "../../inc/Date.hpp"
#include <gtest/gtest.h>

TEST(Date, ValidDates) {
	// valid 31.
	EXPECT_NO_THROW(Date("2012-01-31"));
	EXPECT_NO_THROW(Date("2012-03-31"));
	EXPECT_NO_THROW(Date("2012-05-31"));
	EXPECT_NO_THROW(Date("2012-07-31"));
	EXPECT_NO_THROW(Date("2012-08-31"));
	EXPECT_NO_THROW(Date("2012-10-31"));
	EXPECT_NO_THROW(Date("2012-12-31"));
	// valid february end dates
	EXPECT_NO_THROW(Date("1904-02-28"));
	EXPECT_NO_THROW(Date("2000-02-28"));
	EXPECT_NO_THROW(Date("2004-02-28"));
	// random valid dates
	EXPECT_NO_THROW(Date("2000-02-23"));
	EXPECT_NO_THROW(Date("2000-08-12"));
	EXPECT_NO_THROW(Date("1700-08-12"));
}

TEST(Date, InvalidDates) {
	// invalid 31.
	EXPECT_THROW(Date("2012-02-31"), std::invalid_argument);
	EXPECT_THROW(Date("2012-04-31"), std::invalid_argument);
	EXPECT_THROW(Date("2012-06-31"), std::invalid_argument);
	EXPECT_THROW(Date("2012-09-31"), std::invalid_argument);
	EXPECT_THROW(Date("2012-11-31"), std::invalid_argument);
	// invalid february end dates
	EXPECT_THROW(Date("1900-02-29"), std::invalid_argument);
	EXPECT_THROW(Date("1900-02-30"), std::invalid_argument);
	EXPECT_THROW(Date("1900-02-31"), std::invalid_argument);
	EXPECT_THROW(Date("1901-02-29"), std::invalid_argument);
	// invalid format
	// - wrong characters
	EXPECT_THROW(Date("1900.02.31"), std::invalid_argument);
	EXPECT_THROW(Date("19010229"), std::invalid_argument);
	EXPECT_THROW(Date("1900 02 31"), std::invalid_argument);
	EXPECT_THROW(Date("1900/02/31"), std::invalid_argument);
	EXPECT_THROW(Date("1900a02a31"), std::invalid_argument);
	EXPECT_THROW(Date(""), std::invalid_argument);
	// - wrong numbers month
	EXPECT_THROW(Date("1901-00-12"), std::invalid_argument);
	EXPECT_THROW(Date("1901-13-12"), std::invalid_argument);
	EXPECT_THROW(Date("1901-99-12"), std::invalid_argument);
	// - wrong numbers day
	EXPECT_THROW(Date("1901-12-32"), std::invalid_argument);
	EXPECT_THROW(Date("1901-12-99"), std::invalid_argument);
	EXPECT_THROW(Date("1901-12-00"), std::invalid_argument);
}

TEST(Date, decrementFunction) {
	// last year
	{
		Date date("2012-01-01");
		date.decrementDate();
		EXPECT_EQ(date.getDate(), Date("2011-12-31").getDate());
	}
	// leap year feb
	{
		Date date("2012-03-01");
		date.decrementDate();
		EXPECT_EQ(date.getDate(), Date("2012-02-29").getDate());
	}
	// non leap year feb
	{
		Date date("2013-03-01");
		date.decrementDate();
		EXPECT_EQ(date.getDate(), Date("2013-02-28").getDate());
	}
	// same month
	{
		Date date("2012-04-17");
		date.decrementDate();
		EXPECT_EQ(date.getDate(), Date("2012-04-16").getDate());
	}
}


