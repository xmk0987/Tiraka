// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>

// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


struct Region
{
    RegionID region_id;
    Name region_name;
    std::vector<Coord> region_coordinates;
    std::vector<RegionID> subregions;
    std::vector<StationID> stations;
};


struct Station
{
    StationID id;
    Name stationName;
    Coord coordinates;
    std::map<Time, std::vector<TrainID>> departures;

};



using Station_Database = std::unordered_map<StationID, Station>;
using Region_Database = std::unordered_map<RegionID, Region>;

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: Theta(1)
    // Short rationale for estimate:
    // The size is tracked in use, getting the size is always constant.
    unsigned int station_count();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate:
    // Documentation tells that clear algorithm is linear on size, goes through whole map
    // so its dependant on size
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Goes through all elements in database and inserts them 1 by 1, so dependant on size
    std::vector<StationID> all_stations();

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // insertion to unordered_map equals estimated
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // find to unordered_map equals estimated
    Name get_station_name(StationID id);

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // find to unordered_map equals estimated
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: Theta(nlog(n)
    // Short rationale for estimate: Transform algorithm is constant in time.
    // But std::sort has average case lineartihmic (nlogn) time complexity so that is why
    // it is the estimate of time complexity
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: Theta(nlog(n)
    // Short rationale for estimate: Transform algorithm is constant in time.
    // But std::sort has average case lineartihmic (nlogn) time complexity so that is why
    // it is the estimate of time complexity
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Using forloop to go through database and matching
    // with looked coordinates dependant on size for that reason
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(1) or O(n)
    // Short rationale for estimate: According to documentation unordered map find and
    // insertion are time complexity of O(1) or O(n) them add together will also make one of them
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(1) or O(n)
    // Short rationale for estimate: Find is O(1) or O(n) and vector and unordered map insertion also
    // is O(1) or O(n) which adds up to estimated
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Using forloop to go through database which is O(n)
    // also using find algorithm for vector which is according to documentation sorted = O(logn) and
    // other = O(n) so in this case O(n). Erase is O(n) or O(1) so the superior complexity is O(n)
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Using forloop, sort of vector and find of map
    // which all are O(n). There is a nested forloop but is only accessed at one
    // of the stations which doesnt make it O(n²) for that reason
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // insertion to unordered_map equals estimated
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Goes through all elements in database and inserts them 1 by 1, so dependant on size
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // find to unordered_map equals estimated
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n) or O(1)
    // Short rationale for estimate: Documentation tells the time complexity of
    // find to unordered_map equals estimated
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: All completed procesess have an time complexity
    // of O(n) according to documentation and linear + linear = linear
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: All completed procesess have an time complexity
    // of O(n) according to documentation and linear + linear = linear
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Forloops through regions to find certain station
    // which at worst case will be O(n) and than with recursion which is also O(n) will
    // go through the subregion vectors
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_station(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

private:
    // Add stuff needed for your class implementation here
    Station_Database station_database_;
    Region_Database region_database_;

    std::vector<RegionID> recursive_station_in_regions(RegionID regionid, std::vector<RegionID> wanted);

};

#endif // DATASTRUCTURES_HH
