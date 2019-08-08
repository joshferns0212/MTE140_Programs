//Eric-Khang Dao 20774442
//Joshua Fernandes 20765616

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

class Graph {
	vector<vector<int>> adj_matrix;
	vector<string> names;
	vector<int> distances;

public:
	Graph(string file_name) {
		ifstream fin(file_name.c_str());
		if(fin){
			string input = "";
			int index1, index2, affinity;

			fin >> input;

			while (input != "~") {
				names.push_back(input);
				fin >> input;
			}

			adj_matrix.resize(names.size());

			for (int i = 0; i< names.size(); i++) {
				for (int j = 0; j < names.size(); j++) {
					adj_matrix[i].push_back(i == j ? 0 : 1000);
				}
			}


			while(fin) {
				fin >> input;
				stringstream(input) >> index1;
				fin >> input;
				stringstream(input) >> index2;
				fin >> input;
				stringstream(input) >> affinity;

				adj_matrix[index1][index2] = affinity;
			}

			find_shortest_path();

		} else {
			cout << "File \"" << file_name <<"\"does not exist" << endl;
		}
	}

	void find_shortest_path() {
		for(int i = 0;i < adj_matrix[0].size();i++) //INITIALIZES FIRST ROW IN ADJ MATRIX
			distances.push_back(1000);

		vector<int> visited;
		vector<int> unvisited;

		for (int i = 0; i < names.size(); i++) { //FILL UNVISITED SET WITH ALL NAMES EXCEPT FIRST
			unvisited.push_back(i);
		}

		int current_node = 0;
		int distance_to_current = 0;

		while(!unvisited.empty()) {
			for(int i = 0; i < adj_matrix[current_node].size(); i++) {
				if(distance_to_current + adj_matrix[current_node][i] < distances[i])
					distances[i] = distance_to_current + adj_matrix[current_node][i];
			}

			for(int i = 0; i < unvisited.size(); i++) {
				if(unvisited[i] == current_node)
					unvisited.erase(unvisited.begin() + i);
			}

			visited.push_back(current_node);

			int min_distance = 1000;

			for(int i = 0; i < unvisited.size();i++) {
				if(distances[unvisited[i]] < min_distance) {
					min_distance = distances[unvisited[i]];
					current_node = unvisited[i];
				}
			}
			distance_to_current = min_distance;
		}
	}


	int get_shortest_path(string name) {
		for (int i = 0 ; i < names.size(); i++)
			if (names[i] == name)
				return distances[i];

		return 0;
	}

	int get_number_of_nodes() {
		return names.size();
	}
	string get_name(int index) {
		return names[index];
	}
};

int main() {
	Graph test_graph("DRIVER TEXT FILE.txt"), user_graph("USER CREATED TEXT FILE.txt");

	cout << "DRIVER TEXT FILE" << endl;
	for (int i = 0; i < test_graph.get_number_of_nodes(); i++) {
		cout << "(" << test_graph.get_name(0)<< ")->(" << test_graph.get_name(i) << "): "<< test_graph.get_shortest_path(test_graph.get_name(i)) << endl;
	}

	cout << "USER CREATED TEXT FILE" << endl;
	for (int i = 0; i < user_graph.get_number_of_nodes(); i++) {
		cout << "(" << user_graph.get_name(0)<< ")->(" << user_graph.get_name(i) << "): "<< user_graph.get_shortest_path(user_graph.get_name(i)) << endl;
	}

	return 0;
}
