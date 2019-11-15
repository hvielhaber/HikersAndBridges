#pragma once

#include "HikersAndBridges.h"
#include <string>
#include <vector>
using namespace std;

//
// Mini YAML Parser for loading hikers and bridges in YAML format 
// This is limited YAML, just for the purpose of loading the hikers/bridges data
//
// Example input:
//
// hikers:
//   - speed: 100
//     bridge: 0
//   - speed: 50
//     bridge: 0
//   - speed: 20
//     bridge: 0
//   - speed: 10
//     bridge: 0
//   - speed: 2.5
//     bridge: 1
//   - speed: 25
//     bridge: 2
//   - speed: 15
//     bridge: 2
// 
// bridges:
// 	 - length: 100
// 	 - length: 250
// 	 - length: 150
//

class YamlFileLoader
{
public:
	YamlFileLoader();

	void read_elems(istream& in, vector<Hiker>& hikers, vector<Bridge>& bridges);

private:

	void skip_whitespace(string::iterator& itr, const string::iterator& end);

	const string elem_hikers = "hikers";
	const string elem_bridges = "bridges";
};

