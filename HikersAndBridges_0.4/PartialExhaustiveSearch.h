#pragma once

#include "HikingStrategy.h"

//
// "Partial Exhaustive Search" Strategy
//
// This strategy goes bridge by bridge.
// I.e. each bridge gets cleared before attempting the next bridge.
//
// At each bridge, it generates all possible combinations of hikers 
// to cross the bridge and determines the fastest one.
//

class PartialExhaustiveSearch : public HikingStrategy
{
public:
	PartialExhaustiveSearch(HikersAndBridges& prob);
	
	double solve() override;

private:
	// Recursive search function that generates all possible combinations.
	// Keeps track of the combinations in the candidate vector and stores the best solution\
	// in the solution vector. The cumulative time is the maintained while building each candidate 
	// and the minimum cumulative time is store for the solution vector
	void search(int bridge, bool forward, int nr_hikers_at_start,
		vector<int>& candidate, vector<int>& solution,
		double cumulative_time, double& min_cumulative_time);
};


