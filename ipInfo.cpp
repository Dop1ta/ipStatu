#include<iostream>
#include<fstream>
#include<string>
#include<thread>

using namespace std;

void ip_part1();
void ip_part2();

int main(int argc, char *argv[]) {

	string ping = "ping ";
	string ipS = argv[1];

	cout << ipS << endl;
	ifstream ip(ipS.c_str());
	string linea;

	getline(ip, linea);
	cout << endl << linea << endl;
	linea = ping + linea + " -c " + argv[2];

	system(linea.c_str());

	return 0;

}

void ip_part1() {

}