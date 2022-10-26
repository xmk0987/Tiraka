#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */

void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    int size = vec.size();
    std::vector<int> dublicateVector;

    for(int i = 0; i < size; i++){
        if(vec.at(i) % 2 == 0){
            dublicateVector.push_back(vec.at(i));
            dublicateVector.push_back(vec.at(i));
        }
    }

    vec.clear();
    for(int i = 0; i < dublicateVector.size(); i++){
        vec.push_back(dublicateVector.at(i));
    }


}
