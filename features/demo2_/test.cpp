#include "source.cpp"
#include <stdio.h>

#define BOOST_TEST_MODULE DEMO_2
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Addition_Suite)
BOOST_AUTO_TEST_CASE(Positive_Addition_Test) { 

	BOOST_CHECK(add(4,0)==4); 
}
BOOST_AUTO_TEST_CASE(Negative_Addition_Test){

	BOOST_CHECK(add(-4,0)==-4);
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Subtract_suite)
BOOST_AUTO_TEST_CASE(Positive_Subtract_Test) { 

	BOOST_CHECK(sub(4,0)==4); 
}
BOOST_AUTO_TEST_CASE(Negative_Subtract_Test){

	BOOST_CHECK(sub(0,4)==-4);
}
BOOST_AUTO_TEST_SUITE_END()
