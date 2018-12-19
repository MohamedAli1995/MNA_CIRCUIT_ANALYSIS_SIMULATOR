//
// Created by syrix on 12/16/18.
//
#include<iostream>
#include<string>
#include "Matrix.h"
using namespace std;

//NOTE: boost generates the main for you if you use the BOOST_TEST_DYN_LINK , so we don't need to write main()
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE SIMULATOR
#include<boost/test/unit_test.hpp>
namespace utf = boost::unit_test;

struct MatrixTest {
  MatrixTest() {
    printf("====Constructor====\n");
    n = 3;
    m=3;
    a = new double *[n + m];
    for (int i = 0; i < n + m; i++){
      a[i] = new double[n + m];
    }
  }

  ~MatrixTest() {
    printf("=====Destructor====\n");
    for (int i = 0; i < n + m; i++)
    delete[] a[i];
    delete[] a;
  }

  //TODO: initialize variables here
  Matrix matrix;
  double **a;
  int n,m;
};



BOOST_AUTO_TEST_SUITE(MatrixDeterminant_Suite)

BOOST_FIXTURE_TEST_CASE(Positive_Determinant_Test,MatrixTest) {
  matrix.initilzeMatrix(a, n + m, n + m);
  a[0][0]=1;
  a[0][1]=2;
  a[0][2]=3;
  a[1][0]=4;
  a[1][1]=0;
  a[1][2]=5;
  a[2][0]=6;
  a[2][1]=7;
  a[2][2]=8;
  BOOST_CHECK(matrix.CalcDeterminant(a,3)==45);
}

BOOST_FIXTURE_TEST_CASE(Zero_Determinant_Test,MatrixTest){
  matrix.initilzeMatrix(a, n + m, n + m);
  a[0][0]=1;
  a[0][1]=0;
  a[0][2]=0;
  a[1][0]=0;
  a[1][1]=0;
  a[1][2]=0;
  a[2][0]=0;
  a[2][1]=0;
  a[2][2]=0;
  BOOST_CHECK(matrix.CalcDeterminant(a,3)==0);
}

BOOST_FIXTURE_TEST_CASE(Negative_Determinant_Test,MatrixTest){
  matrix.initilzeMatrix(a, n + m, n + m);
  a[0][0]=-1;
  a[0][1]=1;
  a[0][2]=1;
  a[1][0]=1;
  a[1][1]=9;
  a[1][2]=9;
  a[2][0]=1;
  a[2][1]=1;
  a[2][2]=6;
  BOOST_CHECK(matrix.CalcDeterminant(a,3)==-50);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE(initilzeMatrix_suite,MatrixTest/*,* utf::fixture<MatrixTest>()*/)//to uncomment this part -> update the test case header

BOOST_AUTO_TEST_CASE(zeors_Test) {
  matrix.initilzeMatrix(a, n + m, n + m);
  for(int i =0 ; i<n ; i++){
    for(int j =0 ; j<m ; j++){
      BOOST_CHECK(a[i][j]==0.0);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
