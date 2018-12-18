#include "source.cpp"
#include <stdio.h>

#define BOOST_TEST_MODULE DEMO_4
#include <boost/test/included/unit_test.hpp>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(test3, * utf::depends_on("s1/test1"))
{
  BOOST_CHECK(add(3,0)==1);
}

BOOST_AUTO_TEST_CASE(test4, * utf::depends_on("test3"))
{
  BOOST_CHECK(add(4,0)==1);
}

BOOST_AUTO_TEST_CASE(test5, * utf::depends_on("s1/test2"))
{
  BOOST_CHECK(add(5,0)==1);
}

BOOST_AUTO_TEST_SUITE(s1)

  BOOST_AUTO_TEST_CASE(test1)
  {
    BOOST_CHECK(add(1,0)==1);
  }

  BOOST_AUTO_TEST_CASE(test2, * utf::disabled())
  {
    BOOST_CHECK(add(2,0)==1);
  }

BOOST_AUTO_TEST_SUITE_END()
