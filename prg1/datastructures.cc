// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()=default;

Datastructures::~Datastructures()=default;


unsigned int Datastructures::station_count()
{
    return station_database_.size();
}

void Datastructures::clear_all()
{
    station_database_.clear();
}

std::vector<StationID> Datastructures::all_stations()
{
    std::vector<StationID> all_stations;
    all_stations.reserve(station_database_.size());
    for(auto& station : station_database_){
        all_stations.push_back(station.first);
    }
    return all_stations;
}

bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    std::map<Time, std::vector<TrainID>> departures;
    struct Station station = {id, name, xy, departures};
    return station_database_.insert({id, station}).second;

}

Name Datastructures::get_station_name(StationID id)
{

    const auto station = station_database_.find(id);
    if (station == station_database_.end()){
        return NO_NAME;
    }
    return station->second.stationName;
}

Coord Datastructures::get_station_coordinates(StationID id)
{
    const auto station = station_database_.find(id);
    if (station == station_database_.end()){
        return NO_COORD;
    }
    return station->second.coordinates;
}





std::vector<StationID> Datastructures::stations_alphabetically()
{
    std::vector<Station*> stations{};
    stations.reserve(station_database_.size());

    std::transform(station_database_.begin(), station_database_.end(), std::back_inserter(stations),[](auto& station) {return &station.second;});


    std::sort(stations.begin(), stations.end(), [](const auto& station1, const auto&station2){
        return station1->stationName < station2->stationName;

    });

    std::vector<StationID> stations_ids;

    stations_ids.reserve((station_database_.size()));

    std::transform(stations.begin(), stations.end(),
                   std::back_inserter(stations_ids), [](const auto& station){return station->id;});


    return stations_ids;
}





std::vector<StationID> Datastructures::stations_distance_increasing()
{
    std::vector<Station*> stations{};
    stations.reserve(station_database_.size());

    std::transform(station_database_.begin(), station_database_.end(), std::back_inserter(stations),[](auto& station) {return &station.second;});


    std::sort(stations.begin(), stations.end(), [](const auto& station1, const auto&station2){
        int euclicdic_distance_a = sqrt(pow(station1->coordinates.x,2)+pow(station1->coordinates.y,2));
        int euclicdic_distance_b = sqrt(pow(station2->coordinates.x,2)+pow(station2->coordinates.y,2));
        return euclicdic_distance_a<euclicdic_distance_b;

    });

    std::vector<StationID> stations_ids;

    stations_ids.reserve((station_database_.size()));

    std::transform(stations.begin(), stations.end(),
                   std::back_inserter(stations_ids), [](const auto& station){return station->id;});


    return stations_ids;


}

StationID Datastructures::find_station_with_coord(Coord xy)
{
    for(auto& station : station_database_){
        if(station.second.coordinates == xy){
            return station.first;
        }

    }
    return NO_STATION;
}

bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    auto station = station_database_.find(id);
    if (station == station_database_.end()){
        return false;
    }
    station->second.coordinates = newcoord;
    return true;
}

bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    auto station = station_database_.find(stationid);
    if (station == station_database_.end()){
        return false;
    }
    std::vector<TrainID> trains;
    trains.push_back(trainid);
    return station->second.departures.insert({time, trains}).second;

}

bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    auto station = station_database_.find(stationid);
    if (station == station_database_.end()){
        return false;
    }
    for(auto& station : station_database_){
        auto departure = station.second.departures.find(time);
        if(departure != station.second.departures.end()){
            std::vector<TrainID> trains = station.second.departures.at(time);
            if(std::find(departure->second.begin(), departure->second.end(), trainid) != trains.end()){
                if(trains.size() == 1){
                    station.second.departures.erase(time);
                    return true;
                }
                trains.erase(std::remove(trains.begin(), trains.end(), trainid), trains.end());
                return true;
            }
    }
}
    return false;
}


std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    std::vector<std::pair<Time, TrainID>> returnvector;
    std::pair<Time, TrainID> timetrain;
    auto station = station_database_.find(stationid);
    if (station == station_database_.end()){
        timetrain.first = NO_TIME;
        timetrain.second = NO_TRAIN;
        returnvector.push_back(timetrain);
        return returnvector;
    }
    auto departures = station->second.departures;
    for (auto& x : departures){
        if(x.first >= time){
            std::sort(x.second.begin(), x.second.end());
            timetrain.first = x.first;
            for (auto&& i : x.second){
               timetrain.second = i;
               returnvector.push_back(timetrain);
            }
        }
    }
    return returnvector;
}


bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    std::vector<RegionID> subregions;
    std::vector<StationID> stations;
    struct Region region = {id, name, coords,subregions, stations};
    return region_database_.insert({id,region}).second;
}

std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> all_regions;
    all_regions.reserve(region_database_.size());
    for(auto& region : region_database_){
        all_regions.push_back(region.first);
    }
    return all_regions;
}

Name Datastructures::get_region_name(RegionID id)
{
    const auto region = region_database_.find(id);
    if(region == region_database_.end()){
        return NO_NAME;
    }
    return region->second.region_name;
}

std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    std::vector<Coord> coordinate_vector;
    const auto region = region_database_.find(id);
    if(region != region_database_.end()){
        return region->second.region_coordinates;
    }
    coordinate_vector.push_back(NO_COORD);
    return coordinate_vector;


}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    const auto parentregion = region_database_.find(parentid);
      const auto childregion = region_database_.find(id);
    if(parentregion == region_database_.end() or childregion == region_database_.end()){
        return false;
    }
    for(auto& region : region_database_){
        if (std::find(region.second.subregions.begin(), region.second.subregions.end(), id) != region.second.subregions.end()){
            return false;
        }
    }
    parentregion->second.subregions.push_back(id);
    return true;


}

bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    const auto region = region_database_.find(parentid);
    const auto station = station_database_.find(id);
    if(region == region_database_.end() or station == station_database_.end()){
        return false;
    }
    for(auto& region : region_database_){
        if (std::find(region.second.stations.begin(), region.second.stations.end(), id) != region.second.stations.end()){
            return false;
        }
    }
    region->second.stations.push_back(id);
    return true;

}



std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    const auto station = station_database_.find(id);
    if(station == station_database_.end()){
        return {NO_REGION};
    }
    std::vector<RegionID> found_regions;

   for(auto& region : region_database_){
        if (std::find(region.second.stations.begin(), region.second.stations.end(), id) != region.second.stations.end()){
            found_regions = recursive_station_in_regions(region.first, found_regions);
            return found_regions;

        }
    }
    return found_regions;

}

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("all_subregions_of_region()");
}

std::vector<StationID> Datastructures::stations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("stations_closest_to()");
}

bool Datastructures::remove_station(StationID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_station()");
}

RegionID Datastructures::common_parent_of_regions(RegionID /*id1*/, RegionID /*id2*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("common_parent_of_regions()");
}

std::vector<RegionID> Datastructures::recursive_station_in_regions(RegionID regionid, std::vector<RegionID> wanted)
{


    wanted.push_back(regionid);
    for(const auto& region : region_database_){
        if(std::find(region.second.subregions.begin(), region.second.subregions.end(), regionid) != region.second.subregions.end()){
            wanted = recursive_station_in_regions(region.first, wanted);
        }
    }
    return wanted;
}




