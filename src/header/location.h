#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

#include <vector>
#include <string>
#include "item.h"
#include "direction.h"

using std::string;
using std::vector;

class Location
{
	private:
		const string loc_id;
		string description;
		vector<Item*> items;
		Location *forwards;
		string fPath;
		Location *left;
		string lPath;
		Location *right;
		string rPath;
		Location *backwards;
		string bPath;
		Location **directionToLocation(DirectionT);
		string *directionToPathD(DirectionT);
	public:
		Location(string lID, string d) : loc_id(lID), description(d), items(0), forwards(0), left(0), right(0), backwards(0) { }
		~Location() { }
		const string getLocID() const { return loc_id; }
		string beLookedAt() const;
		void addItem(Item * const i) { items.push_back(i); }
		Location *getPath(DirectionT) const;
		void setPath(DirectionT, Location *, string);
		void removePath(DirectionT);
		bool hasPath(DirectionT);
};

#endif // LOCATION_H_INCLUDED
