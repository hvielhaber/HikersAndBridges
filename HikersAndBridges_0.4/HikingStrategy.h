#pragma once

#include "HikersAndBridges.h"
#include <map>

//
// abstract base class for hiking strategies
//
class HikingStrategy
{
public:
	HikingStrategy(HikersAndBridges& prob);

	// function for solving the hikers/bridges problem
	virtual double solve() = 0;

protected:
	// returns fastest hiker on a bridge
	int fastest_hiker(int bridge) const;

	// calculates time that a hiker needs to cross a bridge
	double crossing_time(int hiker, int bridge) const;

protected:
	HikersAndBridges& problem;	// reference to hikers/bridges problem configuration

	vector<Hiker>& hikers;		// reference to hikers vector
	vector<Bridge>& bridges;	// reference to bridges vector

	int nr_hikers;				// number of hikers (= size of hikers vector)
	int nr_bridges;				// number of bridges (= size of bridges vector)
};

