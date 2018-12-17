#include "source.cpp"
#include <stdio.h>

#define BOOST_TEST_MODULE DEMO_1
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(addition_test) { 

	BOOST_CHECK(add(2,3)==5); 

}
