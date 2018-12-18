#include "source.cpp"
#include <stdio.h>

#define BOOST_TEST_MODULE DEMO_5
#include <boost/test/included/unit_test.hpp>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(test_case1, * utf::label("trivial"))
{
  BOOST_CHECK(add(1,0)==1);
}

BOOST_AUTO_TEST_CASE(test_case2,
  * utf::label("trivial")
  * utf::label("cmp")
  * utf::description("testing equality of ones"))
{
  BOOST_CHECK(add(1,0)==1);
}
