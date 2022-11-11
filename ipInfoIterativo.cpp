#include<iostream>
#include<fstream>
#include<thread>

using namespace std;

void statusIP(string linea, char *nPackage, int i);
void viewData(int total);

struct IPINFO{

	string nIp;
	int nPackege;
	int Ploss;
	
}dataIp[10];

int main(int argc, char *argv[]) {

	int i = 0;

	ifstream ip(argv[1]);
	string linea;

	
	while(getline(ip, linea)){
		dataIp[i].nIp = linea;
		dataIp[i].nPackege = atoi(argv[2]);
		statusIP(linea, argv[2], i);
		i += 1;
	}



	viewData(i);

	// system(("ping "+openFile(argv[1])+" -c "+argv[2] + " > data.txt").c_str());
	// system(("ping "+openFile(argv[1])+" -c "+argv[2] + " > data2.txt").c_str());
	return 0;

}

void statusIP(string linea, char *nPackage, int i){

	string pa = nPackage;
	system(("ping " + linea + " -c " + pa + " | grep -i received > data" +to_string(i)+".txt").c_str());

	// Extraccion de datos generados por el ping

	ifstream data(("data" + to_string(i) + ".txt").c_str());
	string infoS;

	getline(data, infoS);

	int packtLoss = infoS[23] - '0';

	dataIp[i].Ploss = packtLoss;
}

void viewData(int total){

	int i = 0;

	cout << "IP               Trans.      Rec.     Perd.      Estado" << endl;
	cout << "=======================================================" << endl;

	while(i < total){
		cout << dataIp[i].nIp << "        " << dataIp[i].nPackege << "          " << dataIp[i].Ploss << "        ";

		if( dataIp[i].Ploss <= dataIp[i].nPackege && dataIp[i].Ploss > 0){
			cout << dataIp[i].nPackege - dataIp[i].Ploss << "         " << "UP" << endl;
		}else{
			cout << dataIp[i].nPackege - dataIp[i].Ploss << "         " << "DOWN" << endl;
		}

		i += 1;
	}
}