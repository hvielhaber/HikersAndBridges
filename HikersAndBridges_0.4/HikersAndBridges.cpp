#include "HikersAndBridges.h"
#include "YamlFileLoader.h"
#include <fstream>

//
// default ctor
//
HikersAndBridges::HikersAndBridges() {

}

//
// initialize hikers and bridges vectors from text file
//
bool HikersAndBridges::init(const string& filename) {

	// open file for reading
	ifstream fin(filename);
	if (!fin) {
		cerr << "Error opening file " << filename << "\n";
		return false;
	}

	// read configuration from file in YAML format
	YamlFileLoader yaml_file_loader;
	yaml_file_loader.read_elems(fin, hikers, bridges);

	// close file
	fin.close();

	return true;
}
