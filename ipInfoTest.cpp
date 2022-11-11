#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void dataPing(struct IPINFO *data);
void viewData(struct IPINFO *dataIp);
int glo_cont = 0;
pthread_mutex_t mutex;

struct IPINFO
{

  string nIp;
  int nPackege;
  int Ploss;
};

int main(int argc, char *argv[])
{

  // if( argc <= 2 ){
  //   cout << "Se te olvidaron los argumentos" << endl;
  //   return 0;
  // }

  pthread_mutex_init(&mutex, NULL);
  int lineText = 0;

  ifstream ip("archivo_listado_ips.txt");
  string linea;

  while (getline(ip, linea))
  {
    lineText++;
  }
  ip.close();

  struct IPINFO data[lineText];
  thread threads[lineText];

  ifstream ip2("archivo_listado_ips.txt");
  string linea2;
  int cont = 0;
  while (getline(ip2, linea2))
  {
    data[cont].nIp = linea2;
    data[cont].nPackege = 2;

    threads[cont] = thread(dataPing, &data[cont]);

    // cout << data[cont].nIp << "   " << data[cont].nPackege << endl;

    cont++;
  }
  for (int i = 0; i < lineText; i++)
  {
    threads[i].join();
  }
  ip.close();

  // IMPRIMIR DATOS DE LA IP

  cout << "IP               Trans.      Rec.     Perd.      Estado" << endl;
  cout << "=======================================================" << endl;

  for (int i = 0; i < lineText; i++)
  {
    viewData(&data[i]);
  }

  return 0;
}

void dataPing(struct IPINFO *data)
{

  pthread_mutex_lock(&mutex);

  system(("ping " + (data)->nIp + " -c " + to_string((data)->nPackege) + " | grep -i received > data" + to_string(glo_cont) + ".txt").c_str());

  ifstream dataip(("data" + to_string(glo_cont) + ".txt").c_str());
  string infoS;

  getline(dataip, infoS);

  int packtLoss = infoS[23] - '0';

  (data)->Ploss = packtLoss;

  glo_cont++;

  pthread_mutex_unlock(&mutex);
}

void viewData(struct IPINFO *dataIp)
{

  int i = 0;

  cout << dataIp->nIp << "        " << dataIp->nPackege << "          " << dataIp->Ploss << "        ";

  if (dataIp->Ploss <= dataIp->nPackege && dataIp->Ploss > 0)
  {
    cout << dataIp->nPackege - dataIp->Ploss << "         "
         << "UP" << endl;
  }
  else
  {
    cout << dataIp->nPackege - dataIp->Ploss << "         "
         << "DOWN" << endl;
  }

  i += 1;
}