//#include <string>
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <windows.h>
//using namespace std;
//
//void buildTopology();
//void clearFile();
//void SplitString(const string& s, vector<string>& v, const string& c);
//int main() {
//	buildTopology();
//};
//
//void buildTopology() {
//	clearFile();
//
//	ifstream  ifs1;
//	string topology = "topology.txt";
//	ifs1.open(topology);
//	string oneLine;
//
//	int time = 0;
//	while (getline(ifs1, oneLine)) {
//		vector<string> v;
//		SplitString(oneLine, v, " ");
//		Sleep((stoi(v[0]) - time) * 1000);
//		time = stoi(v[0]);
//
//		if (v[1] == "UP") {
//			string NTable = "NeighborTable/" + v[2] + ".txt";
//
//			ofstream ofs;
//			ofs.open(NTable, ios::app);
//			ofs << v[3];
//			ofs << endl;
//			ofs.close();
//		}
//		else if (v[1] == "DOWN") {
//			string NTable = "NeighborTable/" + v[2] + ".txt";
//			//read data and delete in vector
//			ifstream  ifs2;
//			ifs2.open(NTable);
//
//			string oneLine1;
//			vector<string> v1;
//
//			int counter = 0;
//			while (getline(ifs2, oneLine1)) {
//				if (oneLine1 == v[3]) continue;
//				v1.push_back(oneLine1);
//
//			}
//			ifs2.close();
//
//			//rewrite
//			ofstream ofs;
//			ofs.open(NTable, ios::trunc);
//			for (vector<string>::size_type j = 0; j < v1.size(); j++) {
//		
//				ofs << v1[j];
//				ofs << endl;
//			}
//			ofs.close();
//
//		}
//	}
//	ifs1.close();
//}
//
//void clearFile() {
//	for (int i = 0; i <= 9; i++) {
//		string name1 = "NeighborTable/" + to_string(i) + ".txt";
//		string name2 = "toX/to" + to_string(i) + ".txt";
//		string name3 = "fromX/from" + to_string(i) + ".txt";
//		string name4 = "MSset/" + to_string(i) + ".txt";
//		
//		ofstream fileout1(name1, ios::trunc);
//		ofstream fileout2(name2, ios::trunc);
//		ofstream fileout3(name3, ios::trunc);
//		ofstream fileout4(name4, ios::trunc);
//
//		if (!fileout1||!fileout2||!fileout3||!fileout4) {
//			cout << "create file failure...\n";
//			exit(0);
//		}
//		fileout1.close();
//		fileout2.close();
//		fileout3.close();
//		fileout4.close();
//
//	}
//}
// 
//void SplitString(const string& s, vector<string>& v, const string& c) {
//	string::size_type pos1, pos2;
//	pos2 = s.find(c);
//	pos1 = 0;
//	while (string::npos != pos2)
//	{
//		v.push_back(s.substr(pos1, pos2 - pos1));
//
//		pos1 = pos2 + c.size();
//		pos2 = s.find(c, pos1);
//	}
//	if (pos1 != s.length())
//		v.push_back(s.substr(pos1));
//}