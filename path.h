#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <vector>

class Path{
public:
	Path(unsigned int id, unsigned int distance); //creates a new path with one city and one distance (hop number is 1)
	Path(const Path* source); // This constcructor creates a deep copy of a path.
	~Path(); //free memory alocated for this path;

	bool is_in(unsigned int id); //checks if city of passed id is in the path. Returns true if city is in the path, false otherwise.
	Path* add(unsigned int id, unsigned int distance);
	/*	Creates a copy of path with addition of passed id and distance.
		Dynamically creates a new path of hops nr greater by one than itself's hops number.
		First n cities id and first n distances are copied from this object to newly created object.
		n-th+1 id of newly creted object is passed id/
		n-th+1 distance of newly created distance is passed distances.
		This function does not frees memmory allocated for this Path!s
	*/
	void print(std::ostream& my_stream, std::vector<std::string> & names);
	/*	Print the path with cities names and distances beetween them.
		Arguments:
			std::ostream& my_stream:
				The stream on which path will be printed (like std::cout).
			std::vector<std::string> & names:
				Because of the fact that Path knows only ids of the city, no names while printing
				path object we need to some howe tell what is the name of each city in the path.
				Names is vector which indices are cities ids and values are cities names. For example
				name of city of id 7 is names[7].
		This function prints path in reversed order. If city nr 9 receives path to city nr 4 the first city on the path
		is city nr 4. If the user want's to know how to get from city nr 9 to city nr 4 it wants output it to be in order.
		The exemplatory output on stream from this function may be:
		--> Katowice (80) --> Lodz (200) --> Gdansk (340)
	*/
	unsigned int from(); //returns an id of origin city of the path (an id of first city on the path)
	unsigned int get_length(); //return the total length of the path, the sum of all distances in the path.

private:
	unsigned int n; //hops numober (how many cities are in the path)
	unsigned int* the_path;
		/* Variable the_path is one deminsional array. The length of this array is always 2 times n.
		In this array bu turns are id's of cities and distances between them.
		So for example if n is equal 4 (there are four cities in the array, the array may look like this:)
		[4, 234, 2, 450, 7, 750, 13, 123].
		It means that the origin of path is city nr 4, the distance betweend city 4 and city 2 is 450, second
		city on the path is city nr 2 and so on. This path may be received by for example city nr 9. This way sity nr 9 knows
		how to get to city nr 2. Because each city knows it's own id there is no need for destinaton id.
		*/

	unsigned int length; // the total length of the path, the sum of all distances in the path.
	Path(unsigned int* the_path, unsigned int n, unsigned int length);
	/* Creates a new Path with given values.
	NOTE: THIS concructor does not copy context of the_path array to it's owna the path_array, it's just set
	own's the_path pointer to be same as the_path agument.
	*/
};


#endif

