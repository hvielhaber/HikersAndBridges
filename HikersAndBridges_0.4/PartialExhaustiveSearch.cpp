#include "PartialExhaustiveSearch.h"
#include <algorithm>

//
// ctor
//
PartialExhaustiveSearch::PartialExhaustiveSearch(HikersAndBridges& prob) : HikingStrategy(prob) {
}

//
// solve function
//
double PartialExhaustiveSearch::solve() {
	// total time & total distance, initially zero
	double total_time = 0.0;
	double total_distance = 0.0;
	
	for (int bridge = 0; bridge < nr_bridges; bridge++) {

		int nr_hikers_at_start = count_if(hikers.begin(), hikers.end(), [=](const Hiker& hiker) { return hiker.bridge == bridge; });
		vector<int> candidate;
		vector<int> solution;
		double min_cumulative_time = -1.0;

		//
		// recursive function call to search for best solution
		//
		search(bridge, true, nr_hikers_at_start,
			candidate, solution,
			0.0, min_cumulative_time);

		//
		// print solution
		// 
		bool forward = true;
		for (int i = 0; i < solution.size(); forward = !forward) {
			if (forward && (i + 1 < solution.size())) {
				int hiker1 = solution[i];
				int hiker2 = solution[i + 1];
				int hiker, fastest;
				if (hikers[hiker1].speed > hikers[hiker2].speed) {
					fastest = hiker1;
					hiker = hiker2;
				}
				else {
					fastest = hiker2;
					hiker = hiker1;
				}
				double time = crossing_time(hiker, bridge);
				total_time += time;
				T(bridge << '\t' << time << '\t' << total_time << '\t' << (forward ? "FWD" : "BWD") << '\t' << fastest << '\t' << hiker);
				i += 2;
			} else {
				double time = crossing_time(solution[i], bridge);
				total_time += time;
				T(bridge << '\t' << time << '\t' << total_time << '\t' << (forward ? "FWD" : "BWD") << '\t' << solution[i]);
				i++;
			}
		}
		T("Time for crossing bridge " << bridge << ": " << min_cumulative_time);

		// set hikers to next bridge
		for (auto& hiker : hikers) {
			if (hiker.bridge == bridge) {
				hiker.bridge++;
			}
		}
	}

	return total_time;
}

//
// Recursively generates candidate vectors and maintains cumulative time.
// Keeps track of number of hikers at the start of the bridge.
// The recursion ends when this number reaches zero, at which time all hikers have
// crossed the bridge. At this time, the candidate vector contains a possible solution.
// The solution vector will be updated with the candidate vector if the cumulative time of
// the candidate vector falls below the minimum cumulative time of the solution found so far.
//
void PartialExhaustiveSearch::search(int bridge, bool forward, int nr_hikers_at_start, 
	                                 vector<int>& candidate, vector<int>& solution, 
								     double cumulative_time, double& min_cumulative_time) {

	if (nr_hikers_at_start == 0) {
		// 
		// case: no hiker left on start of bridge
		//
		if (cumulative_time < min_cumulative_time || min_cumulative_time  == -1.0) {
			min_cumulative_time = cumulative_time;
			solution = candidate;
		}
		return;
	}

	if (forward) {
		if (nr_hikers_at_start > 1) {
			// 
			// case: 2 hikers cross bridge forward
			//
			for (int i = 0; i < nr_hikers - 1; i++) {
				if (hikers[i].bridge != bridge) {
					continue;
				}
				
				// hiker i crosses bridge
				candidate.push_back(i);
				hikers[i].bridge++;

				for (int j = i + 1; j < nr_hikers; j++) {
					if (hikers[j].bridge != bridge) {
						continue;
					}
					
					// hiker j crosses bridge
					candidate.push_back(j);
					hikers[j].bridge++;
					
					// add crossing time of slower hiker
					int slower_hiker = (hikers[i].speed < hikers[j].speed) ? i : j;
					double time = crossing_time(slower_hiker, bridge);
					
					//
					// recursive function call to search for best solution
					// with two hikers less at the start of the bridge
					//
					search(bridge, false, nr_hikers_at_start - 2,
						candidate, solution,
						cumulative_time + time, min_cumulative_time);

					// undo hiker j's crossing
					candidate.pop_back();
					hikers[j].bridge--;
				}

				// undo hiker i's crossing
				candidate.pop_back();
				hikers[i].bridge--;
			}
		}
		else {
			// 
			// case: 1 hiker crosses bridge forward
			//
			for (int i = 0; i < nr_hikers; i++) {
				if (hikers[i].bridge != bridge) {
					continue;
				}

				// hiker i crosses bridge
				candidate.push_back(i);
				hikers[i].bridge++;

				// add crossing time of hiker i
				double time = crossing_time(i, bridge);

				//
				// recursive function call to search for best solution
				// with one hiker less at the start of the bridge
				//
				search(bridge, false, nr_hikers_at_start - 1,
					candidate, solution,
					cumulative_time + time, min_cumulative_time);

				// undo hiker i's crossing
				candidate.pop_back();
				hikers[i].bridge--;
			}
		}
	}
	else {
		// 
		// case: 1 hiker crosses bridge backward
		//
		for (int i = 0; i < nr_hikers; i++) {
			if (hikers[i].bridge != bridge+1) {
				continue;
			}

			// hiker i crosses bridge backward
			candidate.push_back(i);
			hikers[i].bridge--;

			// add crossing time of hiker i
			double time = crossing_time(i, bridge);

			//
			// recursive function call to search for best solution
			// with one hiker more at the start of the bridge
			//
			search(bridge, true, nr_hikers_at_start + 1,
				candidate, solution,
				cumulative_time + time, min_cumulative_time);

			// undo hiker i's crossing
			candidate.pop_back();
			hikers[i].bridge++;
		}
	}
}
