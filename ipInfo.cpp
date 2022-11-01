#include<iostream>
#include<fstream>
#include<thread>

using namespace std;

void statusIP(string linea, char *nPackage, int i);
void exDatosArchivar(int i);

struct ipInfo{

	string nIp;
	int nPackege;
	int Ploss;
	
}dataIp;

int main(int argc, char *argv[]) {

	int i = 0;

	ifstream ip(argv[1]);
	string linea;
	while(getline(ip, linea)){
		statusIP(linea, argv[2], i);
		i += 1;
	}

	void viewData();

	// system(("ping "+openFile(argv[1])+" -c "+argv[2] + " > data.txt").c_str());
	// system(("ping "+openFile(argv[1])+" -c "+argv[2] + " > data2.txt").c_str());
	return 0;

}

void statusIP(string linea, char *nPackage, int i){

	string pa = nPackage;

	system(("ping " + linea + " -c " + pa + " | grep -i received | grep -v -e '2 packets transmitted,' > data" +to_string(i)+".txt").c_str());

	exDatosArchivar(i);
}w

void exDatosArchivar(int i){

	ifstream data(("data" + to_string(i) + ".txt").c_str());
	string infoS;

	getline(data, infoS);

	cout << endl << infoS << endl;
}

void viewData(){

}