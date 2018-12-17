#include "source.cpp"
#include <stdio.h>

#define BOOST_TEST_MODULE DEMO_3
#include <boost/test/included/unit_test.hpp>

BOOST_FIXTURE_TEST_CASE(Node_Test1 , Node) { 

	BOOST_CHECK(*value == 1); 
	(*value)++;
}


BOOST_FIXTURE_TEST_CASE(Node_Test2 , Node) { 

	BOOST_CHECK(*value == 1); 
	
}


BOOST_FIXTURE_TEST_CASE(Node_Test3 , Node) { 

	BOOST_CHECK(*value == 0); 
}
