/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printEverySecond(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
    int count = 0;
    list<int>::const_iterator it;;
    for(it = lst.begin(); it != lst.end(); ++ it){
        if(count % 2 == 0){
            cout<< *it << " ";
        }
        count += 1;

    }
}
