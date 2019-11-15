#include "FastestHiker.h"

//
// ctor
//
FastestHiker::FastestHiker(HikersAndBridges& prob) : HikingStrategy(prob) {
}

//
// solve function
//
double FastestHiker::solve() {
	
	// set total time initially to zero
	double total_time = 0.0; 

	//
	// iterate over bridges
	//
	for (int bridge = 0; bridge < nr_bridges; bridge++) {
		
		// determine fastest hiker on the current bridge
		int fastest = fastest_hiker(bridge);
		
		//
		// iterate over hikers
		//
		for (int hiker = 0; hiker < nr_hikers; hiker++) {
			double time_fastest = crossing_time(fastest, bridge);
			if (hiker != fastest && hikers[hiker].bridge == bridge) {

				// need to get the fastest hiker back if he is on the other side of the bridge
				if (hikers[fastest].bridge != bridge) {
					total_time += time_fastest;
					hikers[fastest].bridge = bridge;
					T(bridge << '\t' << time_fastest << '\t' << total_time << '\t' << "BWD" << '\t' << fastest);
				}

				// fastest hiker and current hiker cross the bridge
				double time = crossing_time(hiker, bridge);
				total_time += time;
				hikers[hiker].bridge++;
				hikers[fastest].bridge++;
				T(bridge << '\t' << time << '\t' << total_time << '\t' << "FWD" << '\t' << fastest << '\t' << hiker);
			}
		}
	}

	return total_time;
}