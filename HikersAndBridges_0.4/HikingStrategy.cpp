#include "HikingStrategy.h"

//
// ctor
//
HikingStrategy::HikingStrategy(HikersAndBridges& prob) 
	: problem(prob), 
	  hikers(prob.get_hikers()),
	  bridges(prob.get_bridges()),
	  nr_hikers(prob.get_hikers().size()),
	  nr_bridges(prob.get_bridges().size())
{
	
}

//
// determine index of fastest hiker on a particular bridge
//
int HikingStrategy::fastest_hiker(int bridge) const {
	int fastest = -1;
	for (int i = 0; i < hikers.size(); i++) {
		if (hikers[i].bridge == bridge) {
			if (fastest == -1 || hikers[i].speed > hikers[fastest].speed) {
				fastest = i;
			}
		}
	}
	return fastest;
}

//
// determine crossing time of a hiker on a particular bridge
//
double HikingStrategy::crossing_time(int hiker, int bridge) const {
	return bridges[bridge].length / hikers[hiker].speed;
}
