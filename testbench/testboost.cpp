//
// Created by syrix on 12/16/18.
//
#include<iostream>
#include<string>


#define BOOST_TEST_MAIN


//#define BOOST_TEST_DYN_LINK



#define BOOST_TEST_MODULE ADDITION_TEST

#include<boost/test/unit_test.hpp>

int add( int i, int j ) { return i+j; }

BOOST_AUTO_TEST_CASE(addition_test) {

    BOOST_CHECK(add(2,3)==5);

}

