#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    try{
        vector<int>::reverse_iterator i1 = std::find_if(v.rbegin(),v.rend(), [](int i)
            {return i % 2 == 0;});
        return i1;
    }
    catch(exception e){
        return v.rend();
    }

}

