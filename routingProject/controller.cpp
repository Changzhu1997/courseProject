#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void SplitString(const string& s, vector<string>& v, const string& c);
void updateToX();
bool  IsContainsStr(string str, string contains_str);
void buildRoute();
void dfs(int graph[][10], int cur, int target, vector<int> visited, string path, vector<string>& paths);
int main() {
	//updateToX();
	//while (true) {
	//	//sleep();
	//	updateToX();
	//}
	buildRoute();
};

void SplitString(const string& s, vector<string>& v, const string& c) {
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void updateToX() {
	for (int i = 0; i <= 9; i++) {
		// find neighbor
		ifstream  ifs1;
		string topology = "topology.txt";
		vector<string> neighbor;
		ifs1.open(topology);
		string oneLine;

		while (getline(ifs1, oneLine)) {
			vector<string> v;
			SplitString(oneLine, v, " ");
			if ((v[2] == to_string(i)) && (v[1] == "UP"))
				neighbor.push_back(v[3]);
		}
		ifs1.close();

		//read from fromX
		string fromX = "fromX/from" + to_string(i) + ".txt";
		ifstream  ifs2;
		ifs2.open(fromX);
		while (getline(ifs2, oneLine)) {
			//write into neighbor's toX
			cout << (IsContainsStr(oneLine, "TC") || IsContainsStr(oneLine, "Hello"))<<endl;
			if (IsContainsStr(oneLine, "TC") || IsContainsStr(oneLine, "Hello")) continue;
			for (vector<string>::size_type j = 0; j < neighbor.size(); j++) {
				int a = stoi(neighbor[j]);
				string toFile = "toX/to" + to_string(a) + ".txt";
				ofstream ofs;
				ofs.open(toFile, ios::app);
				ofs << oneLine;
				ofs << endl;
				ofs.close();
			}
		}
		ifs2.close();
	}
}

bool  IsContainsStr(string str, string contains_str)
{
	string::size_type idx = str.find(contains_str);
	if (idx != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void buildRoute() {
	for (int i = 0; i <= 0; i++) {
		int graph[10][10];
		// build graph
		string toX = "toX/to" + to_string(i) + ".txt";
		ifstream  ifs1;
		ifs1.open(toX);
		string oneLine;
		while (getline(ifs1, oneLine)) {
			if (IsContainsStr(oneLine, "DATA")) {
				continue;
			}
			else if (IsContainsStr(oneLine, "Hello")) {
				vector<string> v;
				SplitString(oneLine, v, " ");
				int source = stoi(v[0]);
				string dest = v[3];
				for (int j = 0; j < dest.length(); j++) {
					int d = (int(dest[j]) - 48);
					graph[source][d] = 1;
				}
			}
			else if (IsContainsStr(oneLine, "TC")) {
				vector<string> v;
				SplitString(oneLine, v, " ");
				int source = stoi(v[2]);
				string dest = v[4];
				for (int j = 0; j < dest.length(); j++) {
					int d = (int(dest[j]) - 48);
					graph[source][d] = 1;
					graph[d][source] = 1;
				}

			}
			else {
				string sourcefile = "NeighborTable/" + to_string(i) + ".txt";
				vector<string> v;
				SplitString(oneLine, v, " ");
				int source = stoi(v[2]);
					string oneLine3;
					ifstream  ifs;
					ifs.open(sourcefile);
					while (getline(ifs, oneLine3)) {
						graph[source][stoi(oneLine3)] = 1;
					}
			
			}

		}
		ifs1.close();

		//find route to dest
		ifstream  ifs2;
		ifs2.open(toX);
		string oneLine1;
		
		while (getline(ifs2, oneLine1)) {
			if (IsContainsStr(oneLine1, "DATA")) {
				vector<string> v;
				SplitString(oneLine1, v, " ");
				int cur = stoi(v[2]);
				int target = stoi(v[4]);
				vector<string> paths;
				vector<int> visited;
				visited.push_back(cur);
				string path = v[2];
				dfs(graph, cur, target, visited, path, paths);
				
				string shortPath;
				int length = 10;
				for (vector<string>::size_type j = 0; j < paths.size(); j++) {
					if (paths[j].length() <= length) {
						length = paths[j].length();
						shortPath = paths[j];
					}
				}
				cout << shortPath;
			// send data 

				for (int i = 1; i < shortPath.length(); i++) {
					string temp;
					temp.push_back(shortPath[i]);
					string toFile = "toX/to" + temp + ".txt";
					ofstream ofs;
					ofs.open(toFile, ios::app);
					ofs << oneLine1;
					ofs << endl;
					ofs.close();
				}
			}
		}
		ifs2.close();
	}
}

void dfs(int graph[][10], int cur, int target, vector<int> visited, string path,vector<string>& paths) {
	for (int i = 0; i < 10; i++) {
		if ((graph[cur][i]==1) && !count(visited.begin(), visited.end(), i)) {
			string newPath = path + to_string(i);
			//cout << newPath << endl;
			if(i == target){
				paths.push_back(newPath);
				return;
			}
			visited.push_back(i);
			dfs(graph, i, target, visited, newPath, paths);
			vector<int>::iterator it = visited.begin();
			for (; it != visited.end();)
			{
				if (*it == i)
					
					it = visited.erase(it);
				else
					
					++it;
			}
		}
	}
}
