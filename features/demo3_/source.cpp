#include <stdio.h>

int add(int x, int y) { 

	return x + y; 
}

int sub(int x, int y) { 
	
	return x - y; 
}

struct Node {

  Node() {
 
	  value = new int;
      	  *value = 0;
	  printf("====Node constructor====\n");
  }
  ~Node() { 

	  delete value;
	  printf("=====Node Destructor====\n");
  }


  void setup()
  {
	  printf("====Node Setup====\n");
  }
  void teardown()
  {
	  printf("==Node Teardown====\n");
  }
  int *value;
};


