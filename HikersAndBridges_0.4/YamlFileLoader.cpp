#include "YamlFileLoader.h"

#include <algorithm>
#include <fstream>
#include <sstream>

//
// default ctor
//
YamlFileLoader::YamlFileLoader() {

}

//
// read the YAML elements for hikers/bridges from input stream
//
void YamlFileLoader::read_elems(istream& in, vector<Hiker>& hikers, vector<Bridge>& bridges) {
	string elem;
	string line;
	while (getline(in, line)) {
		// check if outermost tag
		if (line.size() > 0 && !isspace(line[0])) {
			if (line == "hikers:") {
				elem = elem_hikers;
			}
			else if (line == "bridges:") {
				elem = elem_bridges;
			}
			continue;
		}

		// look for element tag '-' indicating the start of next hiker
		string::iterator itr = line.begin();
		skip_whitespace(itr, line.end());
		if (itr != line.end()) {
			if (*itr == '-' && (itr + 1) != line.end() && isspace(*(itr + 1))) {
				if (elem == elem_hikers) {
					hikers.push_back(Hiker());
				}
				else if (elem == elem_bridges) {
					bridges.push_back(Bridge());
				}
				itr += 2;
				skip_whitespace(itr, line.end());
			}
		}

		// read attribute
		if (itr != line.end()) {
			stringstream sstream(line.substr(itr - line.begin(), line.end() - line.begin()));
			string attr;
			sstream >> attr;
			if (elem == elem_hikers) {
				if (attr == "speed:") {
					double speed;
					sstream >> speed;
					hikers[hikers.size() - 1].speed = speed;
				}
				else if (attr == "bridge:") {
					int bridge;
					sstream >> bridge;
					hikers[hikers.size() - 1].bridge = bridge;
				}
			}
			else if (elem == elem_bridges) {
				if (attr == "length:") {
					double length;
					sstream >> length;
					bridges[bridges.size() - 1].length = length;
				}
			}
		}
	}
}

//
// skip whitespace characters
// modifies itr to point to first non-whitespace character in string
//
void YamlFileLoader::skip_whitespace(string::iterator& itr, const string::iterator& end) {
	itr = find_if(itr, end, [](char c) { return !isspace(c); });
}


