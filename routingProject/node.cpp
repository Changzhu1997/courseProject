//#include <string>
//#include <fstream>
//#include <iostream>
//#include <numeric>
//#include <vector>
//using namespace std;
//void sendHello(string id);
//void sendTopoloy(string id);
//string MPRselect(string id);
//void sendDataMsg(string id, string data);
//void writeIntoMSs(string MPR, string id);
//
//int main(int argc, char* argv[]) {
//	if (argc == 5) {
//		sendDataMsg(argv[1], argv[3]);
//		//while sleep
//		sendHello(argv[1]);
//		sendTopoloy(argv[1]);
//	}
//	else if (argc == 3) {
//		writeIntoMSs(MPRselect(argv[1]), argv[1]);
//		//while loop	
//		//sleep(1)
//		sendHello(argv[1]);
//		//sleep 5 sec to send 
//		sendTopoloy(argv[1]);
//	}
//	else {
//		cout << "Invalid Input !!!" << endl;
//	}
//}
//
//void sendDataMsg(string id, string data) {
//	string sourcefile = "fromx/from" + id + ".txt";
//	ofstream outfile;
//	outfile.open(sourcefile, ios::app);
//	outfile << data << endl;
//	outfile.close();
//}
//
//void sendHello(string id) {
//	string sourcefile = "NeighborTable/" + id + ".txt";
//	string oneLine;
//	ifstream  ifs;
//	ifs.open(sourcefile);
//	vector<string> neighborlist;
//	while (getline(ifs, oneLine)) {
//		neighborlist.push_back(oneLine);
//	}
//	ifs.close();
//
//	string nblist;
//	nblist = accumulate(neighborlist.begin(), neighborlist.end(), nblist);
//	string hello = id + " Hello Neighbor:" + nblist.c_str() + " MPR:" + MPRselect(id);
//	//cout << hello;
//
//	for (vector<string>::size_type j = 0; j < neighborlist.size(); j++)
//	{
//		int a = stoi(neighborlist[j]);
//		string nebFile = "toX/to" + to_string(a) + ".txt";
//		string selfFile = "fromX/from" + id + ".txt";
//		//cout << nebFile << endl;
//		ofstream ofs1;
//		ofs1.open(nebFile, ios::app);
//		ofs1 << hello << endl;
//		ofs1.close();
//
//		ofstream ofs2;
//		ofs2.open(selfFile, ios::app);
//		ofs2 << hello << endl;
//		ofs2.close();
//	}
//}
//
//string MPRselect(string id) {
//	//find neighbor
//	string sourcefile = "NeighborTable/" + id + ".txt";
//	string oneLine;
//	ifstream  ifs;
//	ifs.open(sourcefile);
//	vector<string> neighborlist;
//	while (getline(ifs, oneLine)) {
//		neighborlist.push_back(oneLine);
//	}
//	ifs.close();
//
//
//	//select MPR
//	int count = 0;
//	string MPR;
//	for (vector<string>::size_type j = 0; j < neighborlist.size(); j++)
//	{
//		string sourcefile = "NeighborTable/" + neighborlist[j] + ".txt";
//		ifstream  ifs1;
//		ifs1.open(sourcefile);
//		int temp = 0;
//		while (getline(ifs1, oneLine)) {
//			temp += 1;
//		}
//		ifs1.close();
//		if (temp >= count) {
//			MPR = neighborlist[j];
//			count = temp;
//		}
//		ifs1.close();
//	}
//	return MPR;
//}
//
//void writeIntoMSs(string MPR, string id) {
//	//write into MSset of MPR
//	int b = stoi(MPR);
//	string MSs = "MSset/" + to_string(b) + ".txt";
//	ofstream ofs;
//	ofs.open(MSs, ios::app);
//	ofs << id;
//	ofs << endl;
//	ofs.close();
//}
//
//void sendTopoloy(string id) {
//	//sendTopoly msg to all node 
//	int b = stoi(id);
//	string MSs = "MSset/" + to_string(b) + ".txt";
//	ifstream  ifs;
//	ifs.open(MSs);
//	string oneLine;
//	string msSet;
//	string mpr = MPRselect(id);
//	while (getline(ifs, oneLine)) {
//		if (oneLine == "") break;
//		msSet.append(oneLine,0,1);
//	}
//
//	for (int i = 0; i <= 9; i++) {
//		if (msSet != "") break;
//		if (to_string(i) == id) continue;
//
//		string toX = "toX/to" + to_string(i) + ".txt";
//		string selfFile = "fromX/from" + id + ".txt";
//		ofstream  ofs;
//		ofstream ofs2;
//		ofs.open(toX, ios::app);
//		ofs2.open(selfFile, ios::app);
//
//		string tpMsg =  "TC Src: "+ id +" MS： " + msSet;
//		ofs << tpMsg << endl;
//		ofs2 << tpMsg << endl;
//		
//		ofs.close();
//		ofs2.close();
//	}
//
//	ifs.close();
//}
//
