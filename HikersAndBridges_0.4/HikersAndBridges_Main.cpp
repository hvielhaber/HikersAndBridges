// HikersAndBridges_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HikersAndBridges.h"
#include "HikingStrategy.h"
#include "FastestHiker.h"
#include "PartialExhaustiveSearch.h"

#include <chrono>

static void usage() {
	cerr << "Usage: HikersAndBridges <filename> <strategy>\n";
	cerr << "   <filename> ... YAML configuration file with hikers/bridges configuration\n";
	cerr << "   <strategy> ... strategy for solving the problem, possible values:\n";
	cerr << "                       fastest_hiker\n";
	cerr << "                       partial_exhaustive_search\n";
}

int main(int argc, char* argv[])
{
	//
	// check command line arguments
	//
	if (argc < 3) {
		usage();
		exit(1);
	}
	
	//
	// create and load configuration
	//
	HikersAndBridges hikers_and_bridges;
	if (!hikers_and_bridges.init(argv[1])) {
		cerr << "Initialization failed\n";
		return 1;
	}

	//
	// create strategy
	//
	string str_strategy = argv[2];
	HikingStrategy* strategy = NULL;
	if (str_strategy == "fastest_hiker") {
		strategy = new FastestHiker(hikers_and_bridges);
	} else if (str_strategy == "partial_exhaustive_search") {
		strategy = new PartialExhaustiveSearch(hikers_and_bridges);
	}
	if (strategy == NULL) {
		usage();
		exit(1);
	}
	
	//
	// solve the problem via strategy
	//
	T("bridge\ttime\ttotal time\tdirection\thiker 1\thiker 2");
	auto start_time = std::chrono::high_resolution_clock::now();
	double time = strategy->solve();
	auto finish_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_time = finish_time - start_time;

	cout << "Result - Total Time: " << time << "\n";
	cout << "Elapsed Time (sec): " << elapsed_time.count() << "\n";

	return 0;
}
