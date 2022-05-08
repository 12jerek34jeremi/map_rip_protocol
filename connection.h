#ifndef CONNECTION_H
#define CONNECTION_H
#include "path.h"
#include <iostream>
#include <vector>

class Connection
{
public:
	Connection(const Path* the_path);
	/* This constructor creates a new Connection object. Best path is set to the_path and second_best_path
		is set to nullptr. Because there is no sense in keepeing in connections table a Connection object with
		both best_path and second_best_path being nullptr (connection with no path) this class does not allow existance of
		such a Connection object.
	*/
	Connection(const Connection& source); //copy constructor, creates a deep copy
	~Connection(); //Destructor frees memmory allocated for both paths and this object
	void update(const Path* the_path);
	/* Update functions compares passed path (the_path) with the best_path and second_the best path
		of this object.
		In case thath passed path is better (shorter) than at least one of the object's path this functions
		removes one of object's paths and add the_path to the object.
		In case that path is worse (longer) than each of the object paths this frees memory allocated for passed path.
		Function throws an exception if first city on the passed path it's different that first city of current best path of this object.
	*/
	void print(std::ostream& stream, const std::vector<std::string> & names) const;
	/*
	Print's paths to the destination.
	In case that there is only one known path to destination this information will be printed. (when second_best_path is nullptr)
	In case that there are two knows path they both will be printed.
	*/

private:
	const Path* best_path; //this is the shortets known path to destination
	const Path* second_best_path;
	/*In case of only one known path this is set to nullptr. Otherwise it is second best path. Second best path is
		always equal to or shorter than best path.
	*/
	const unsigned int destination;
	/*The first city to be on best_path and on the second_best_path. They must be the same cities.
	*/
};

#endif // !CONNECTION_H