//#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>

#include "test.hh"

using namespace std;


void usage()
{
    cout << "Usage: iterator_invalidation <test_function> <test_num> [<num_of_items>]" << endl;
    cout << "  test_function: 1|2|3 (number of the function to test as in invalidation1.cc, invalidation2.cc, ...)" << endl;
    cout << "  test_num: number of the test performed on the function  (1-3)" << endl;
    cout << "   num_of_items: number of items in the test vector (optional, default=10)" << endl;
    cout << "Example:" << endl;
    cout << "  iterator_invalidation 3 1    (test duplicateEvenRemoveUneven() with test 1, where v1 should equal with s1)" << endl;
}

int getRandom(int upper)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, upper);
  return dis(gen);
}

std::vector<int> getRandomVector(int size)
{
  std::vector<int> v;

  for (int i = 0; i < size; i++) {
    v.push_back(getRandom(size * 4));
  }

  return v;
}

std::vector<int> getSequence(int size)
{
  std::vector<int> v(size);

  const int rnd = getRandom(size);

  for (int x = 0; x < size; ++x) {
    v[x] = rnd + x;
  }

  return v;
}

std::map<string, int> getMap(const std::vector<int>& v)
{
  std::map<string, int> m;
  for (std::size_t i = 0; i < v.size(); i++) {
    m.insert( std::pair<string, int>("val" + std::to_string(i) , v[i]) );
  }
  return m;
}

void printVector(const std::vector<int>& v)
{
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl << endl;
}

void printMap(const std::map<string, int>& m)
{
  for (auto it = m.begin(); it != m.end(); it++) {
    cout << "{" << it->first << " : " << it->second << "} ";
  }
	cout << endl << endl;
}

void testDuplicateEvenRemoveUneven(int test_id) {
    cout << "Case " << test_id <<": Testing function duplicateEvenRemoveUneven() with the following data:" << endl << endl;
    switch(test_id){
    case 1:
    {
        std::vector<int> v1 = {1, 2, 3, 4};
        std::vector<int> s1 = {2, 2, 4, 4};
        v1.shrink_to_fit();
        printVector(v1);
        duplicateEvenRemoveUneven(v1);
        if(v1 == s1) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector after duplicateEvenRemoveUneven() was called in the case:" << endl << endl;
        printVector(v1);
        break;
    }
    case 2:
    {
        std::vector<int> v2 = {1, 2, 2, 4, 4};
        v2.shrink_to_fit();
        printVector(v2);
        duplicateEvenRemoveUneven(v2);

        std::vector<int> s2 = {2, 2, 2, 2, 4, 4, 4, 4};


        if(v2 == s2) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector after duplicateEvenRemoveUneven():" << endl << endl;
        printVector(v2);

        break;
    }
    case 3:
    {
        std::vector<int> v3 = {1, 2, 3 };
        std::vector<int> s3 = {2, 2};
        v3.shrink_to_fit();
        printVector(v3);
        duplicateEvenRemoveUneven(v3);
        if(v3 == s3) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector after duplicateEvenRemoveUneven():" << endl << endl;
        printVector(v3);

        break;
    }
    default:
      cout << "ERROR: Unknown test for duplicateEvenRemoveUneven: " << test_id << endl;
      cout << "       Valid values are: 1, 2, 3." << endl;
      usage();
      break;
    }


}


void testAscendingVector(int test_id, int size) {
    cout << "Case " << test_id <<": Testing function ascendingVector() with the following data:" << endl << endl;
    switch(test_id){
    case 1:
    {
        std::vector<int> s1 = {0, 1, 2, 3};
        cout << "Size: " << s1.size() << endl;


        std::vector<int> v1 = ascendingVector(s1.size());
        if(v1 == s1) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector created after ascendingVector() was called in the case:" << endl;
        printVector(v1);
        break;
    }
    case 2:
    {
        std::vector<int> s2 = {0, 1, 2, 3, 4, 5, 6, 7};
        cout << "Size: " << s2.size() << endl;
        std::vector<int> v2 = ascendingVector(s2.size());


        if(v2 == s2) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector after ascendingVector():" << endl << endl;
        printVector(v2);

        break;
    }
    case 3:
    {

        cout << "Size: " << size << endl;
        std::vector<int> v3 = ascendingVector(size);

        cout << "The vector after ascendingVector():" << endl << endl;
        printVector(v3);

        break;
    }
    default:
      cout << "ERROR: Unknown test for testAscendingVector: " << test_id << endl;
      cout << "       Valid values are: 1, 2, 3." << endl;
      usage();
      break;
    }
}

void testEraseEverySecond(int test_id, int size) {
    cout << "Case " << test_id <<": Testing function eraseEverySecond() with the following data:" << endl << endl;
    switch(test_id){
    case 1:
    {
        std::vector<int> v1 = {0, 1};
        v1.shrink_to_fit();
        std::vector<int> s1 = {0};
        printVector(v1);

        eraseEverySecond(v1);

        if(v1 == s1) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector created after eraseEverySecond() was called in the case:" << endl;
        printVector(v1);
        break;
    }
    case 2:
    {
        std::vector<int> v2 = {0, 3, 1, 7};
        v2.shrink_to_fit();
        std::vector<int> s2 = {0, 1};
        printVector(v2);

        eraseEverySecond(v2);

        if(v2 == s2) {
            cout << "The tested vector from your function is equal with the solution vector." << endl;
        }
        else {
            cout << "The tested vector is not equal with the solution vector." << endl;
        }

        cout << "The vector after eraseEverySecond():" << endl << endl;
        printVector(v2);

        break;
    }
    case 3:
    {
        std::vector<int> v3 = getRandomVector(size);
        v3.shrink_to_fit();
        cout << "Size: " << size << endl;
        printVector(v3);

        eraseEverySecond(v3);


        cout << "The vector after eraseEverySecond():" << endl << endl;
        printVector(v3);

        break;
    }
    default:
      cout << "ERROR: Unknown test for eraseEverySecond: " << test_id << endl;
      cout << "       Valid values are: 1, 2, 3." << endl;
      usage();
      break;
    }
}


void test(int func_id, int test_id, int size)
{

  switch (func_id)
  {
  case 1:
  {
      testAscendingVector(test_id, size);
      break;
  }
  case 2:
  {
      testEraseEverySecond(test_id, size);
      break;
  }
  case 3:
  {
    testDuplicateEvenRemoveUneven(test_id);
    break;
  }
  default:
    cout << "ERROR: Unknown function to test: " << func_id << endl;
    cout << "       Valid values are:" << endl;
    cout << "       3 (=testing duplicateEvenRemoveUneven function)" << endl;
    cout << "       2 (=testing eraseEverySecond function)" << endl;
    cout << "       1 (=testing ascendingVector function)" << endl;
    

    usage();
    break;
  }
}

int main(int argc, char *argv[])
{
  // function number must be given as the first command line argument, test number as second.
  if (argc < 3) {
    cout << "Must be given atleast 2 arguments to function: func_id and test_id" << endl;
    usage();
    return EXIT_FAILURE;
  }

  char *p;
  long l_func = strtol(argv[1], &p, 10);
  int func_id = (int)l_func;

  long l_test = strtol(argv[2], &p, 10);
  int test_id = (int)l_test;

  // default value for size and search value
  int size = 10;

  if (argc > 3) {
    long l_size = strtol(argv[3], &p, 10);
    size = (int)l_size;
  }

  if (size < 0) {
    cout << "ERROR: Invalid number of items: " << size << endl;
    cout << "       Number of items should be an integer larger than or equal to 0." << endl;
    usage();
    return EXIT_FAILURE;
  }

  test(func_id, test_id, size);
  return EXIT_SUCCESS;
}
