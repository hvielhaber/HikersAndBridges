#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//
// hiker data
//
struct Hiker
{
	double	speed;		// hiking speed - feet/min 
	int		bridge;		// number of bridge
};

//
// bridge data
//
struct Bridge
{
	double	length;		// bridge length - feet 
};

//
// class containing the hikers/bridges problem configuration
//
class HikersAndBridges
{
public:
	HikersAndBridges();

	bool init(const string& filename);

	vector<Hiker>& get_hikers() { return hikers; }
	vector<Bridge>& get_bridges() { return bridges; }

private:
	// store bridges and hikers in vectors
	// identify both bridges and hikers as indexes in the vectors
	vector<Hiker> hikers;
	vector<Bridge> bridges;
};

// trace macro
#define T(s) cout << s << '\n'
