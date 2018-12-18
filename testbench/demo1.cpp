//
// Created by syrix on 12/16/18.
//
#include<iostream>
#include<string>
#include "Simulator.h"
using namespace std;

//NOTE: boost generates the main for you if you use the BOOST_TEST_DYN_LINK , so we don't need to write main()
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE NETLIST
#include<boost/test/unit_test.hpp>



BOOST_AUTO_TEST_CASE(Netlist_test1) {
  string netlistFile = "testbench/input1.txt";
  Simulator sim(netlistFile);
  BOOST_CHECK(sim.netlist.getNodesCount()==2);
  BOOST_CHECK(sim.netlist.getVoltageSourceCount()==1);
  BOOST_CHECK(sim.netlist.hasActiveComponents==true);
}

BOOST_AUTO_TEST_CASE(Netlist_test2) {
  string netlistFile = "testbench/input2.txt";
  Simulator sim(netlistFile);
  BOOST_CHECK(sim.netlist.getNodesCount()==2);
  BOOST_CHECK(sim.netlist.getVoltageSourceCount()==1);
  BOOST_CHECK(sim.netlist.hasActiveComponents==false);
}

BOOST_AUTO_TEST_CASE(Netlist_test3) {
  string netlistFile = "testbench/input3.txt";
  Simulator sim(netlistFile);
  BOOST_CHECK(sim.netlist.getNodesCount()==5);
  BOOST_CHECK(sim.netlist.getVoltageSourceCount()==2);
  BOOST_CHECK(sim.netlist.hasActiveComponents==true);
}


BOOST_AUTO_TEST_CASE(Netlist_test4) {
  string netlistFile = "testbench/input4.txt";
  Simulator sim(netlistFile);
  BOOST_CHECK(sim.netlist.getNodesCount()==13);
  BOOST_CHECK(sim.netlist.getVoltageSourceCount()==5);
  BOOST_CHECK(sim.netlist.hasActiveComponents==true);
}
