#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @brief sort a given vector to an descending order
 *
 * @param v a vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortDesc(std::vector<int>& v)
{
    try{
        reverse(v.begin(), v.end());
        sort(v.begin(), v.end());

    }
    catch(int e){
        return EXIT_FAILURE;
    }


  return EXIT_SUCCESS;

}



