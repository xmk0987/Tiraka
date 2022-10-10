#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Return an iterator which points to the first instance of the given value
 *        If the value is not found, return v.end()
 * @param v
 * @param given
 * @return std::vector<int>::iterator
 */
std::vector<int>::iterator findGivenValue(std::vector<int>& v, int given)
{
    std::vector<int>::iterator it;
    it = find(v.begin(),v.end(),given);
    if(it!=v.end()){
        return it;
    }
    return v.end();
}
