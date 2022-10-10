/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printHalf(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
    int halfsize = lst.size()/2;
    int  count = 0;
    list<int>::const_iterator it;;
    for(it = lst.begin(); it != lst.end(); ++ it){
        if(count < halfsize){
            cout<< *it << " ";
        }
        count += 1;

    }

}
