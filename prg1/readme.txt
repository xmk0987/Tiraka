Onni Vitikainen
H292259

Tiraka Coding Project
Documentation


I chose unordered_map as the general data structure because it generally had the fastest operations for all operations, insertion, accessm erase, find were all either O(1) or O(n) level, which is why it was by far the fastest and also the most reasonable in terms of the task. It was important to get information with the id, so I then made the id the keys to the folder and the struct as a value, because of course you can put a lot of information in the struct and it is easy to access it when it is as an id value. I also decided to create two separate database unordered_maps for regions and stations, because I was able to keep the code clear for this and in terms of speed it seemed smart, since things related to the region were needed for the most part in their own functions and those related to the Station, so it seemed pointless to mix them up.

 I then decided to create vectors in the Region Database, which then contained all subregions or Stations belonging to the region or their ids. I chose vector because it also has good basic speeds for all functions and it was convenient for this purpose, because maybe you wanted to store many different Stations or subregions per region and vector had all the functions I needed to use them.

Here are explanations for some of the more complex functions why I did what I did, where I didn't just use a basic find, clear, etc ...


stations_alphabetically()

	I used reserve on the vectors I was gonna create to avoid any memory problems. I decided to use a vector of pointers because I actually didnt need the whole Station structs in the vector I just wanted to access the name part of them.
	With transform it was very simple and fast to create a vector from the database without using forloops so I didnt have to use any nested loops. 

	Sort is used to get alphabetical order and than transform the sorted name list back to the ids easily with transform to a idvector.



stations_distance_increasing()

	Same idea as in stations_alphabetically()



remove_departure()

	Here there probably was a better way to do it. But I went with a for loop and a few if statements to find the right departure to remove. Time complexity wise this function was not terrible as it only loops once through database in worst case.


station_departures_after()

	Here also not optimal way probably, but didn't come up with anything else. First error check ofcourse. Than I just looped through the given departures vector according to stationid and found all times that where bigger or equal than the wanted time and sorted the departures to right order. Than just added them to the pair and pushed it into pair vector.


station_in_regions()

	I decided to loop through the database to find the wanted station. When found I had a recursive function that created the  vector of all the subregions. Recursive function seemed the most optimal way in this function and that is why I used it. Didn't see anyother way except maybe a tree, but the recursive function was way easier to do with my chosen database.
	

