#pragma once

#include "HikingStrategy.h"

//
// "Fastest Hiker" Strategy
//
// This strategy goes bridge by bridge.
// I.e. each bridge gets cleared before attempting the next bridge.
//
// At each bridge, it determines the fastest hiker. 
// This hiker walks with each hiker to next bridge and then
// goes back to fetch the next hiker, until all hikers are brought across.
//

class FastestHiker: public HikingStrategy 
{
public:
	FastestHiker(HikersAndBridges& prob);

	double solve() override;
};

