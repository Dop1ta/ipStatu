#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

// declaracion de funciones que se ocupan y variables.
void dataPing(struct IPINFO *data);
void viewData(struct IPINFO *dataIp);
int glo_cont = 0;
pthread_mutex_t mutex;

// estructura donde se guardaran los datos de la informacion de la ip.
struct IPINFO
{

  string nIp;
  int nPackege;
  int Ploss;
};

int main(int argc, char *argv[])
{

  // verificacion de que se entreguen los dos parametros al iniciar.
  if (argc <= 2)
  {
    cout << "Se te olvidaron los argumentos" << endl;
    return 0;
  }

  // inicializacion de mutex.
  pthread_mutex_init(&mutex, NULL);

  // abriendo archivo para contar la cantidad de lineas que posee.
  int lineText = 0;
  ifstream ip(argv[1]);
  string linea;

  while (getline(ip, linea))
  {
    lineText++;
  }
  ip.close();

  // definicion de structura y thread segun la cantidad de lineas que contiene el archivo.
  struct IPINFO data[lineText];
  thread threads[lineText];

  // apertura por segunda ves el archivo de listas de ip.
  ifstream ip2(argv[1]);
  string linea2;
  int cont = 0;
  while (getline(ip2, linea2))
  {
    // guardado de ip y numero de paquetes a enviar en la estructura.
    data[cont].nIp = linea2;
    data[cont].nPackege = atoi(argv[2]);

    // creacion de threads
    threads[cont] = thread(dataPing, &data[cont]);

    cont++;
  }

  // bloquea al thread llamante hasta que el thread llamado acabe de ejecutar su método run().
  for (int i = 0; i < lineText; i++)
  {
    threads[i].join();
  }
  ip.close();

  // se hace un clear y un make clean para que no queden archivos en el espacio de trabajo
  system("make clean");
  system("clear");

  // titulo de la infomacion de las ip
  cout << "IP"
       << "\t \t \t"
       << "Trans. \t Rec. \t Perd. \t Estado" << endl;
  cout << "=================================================================" << endl;

  for (int i = 0; i < lineText; i++)
  {
    viewData(&data[i]);
  }

  return 0;
}

// funcion donde se hace el ping a las ip y se guarda en un archivo para leer la informacion que arroja el comando ping
void dataPing(struct IPINFO *data)
{

  pthread_mutex_lock(&mutex);

  // hace ping a la ip y crea un archivo con la informacion dada
  system(("ping " + (data)->nIp + " -c " + to_string((data)->nPackege) + " | grep -i received > data" + to_string(glo_cont) + ".txt").c_str());

  // abre la informacion dada anterior
  ifstream dataip(("data" + to_string(glo_cont) + ".txt").c_str());
  string infoS;

  // busca la informacion necesaria a conseguir.
  getline(dataip, infoS);
  string packetLoss = "";
  int i = 0;

  while (infoS[i] != ',')
  {
    i++;
  }
  i += 2;
  while (infoS[i] != ' ')
  {
    packetLoss = packetLoss + infoS[i];
    i++;
  }

  (data)->Ploss = stoi(packetLoss);

  system(("rm -f data" + to_string(glo_cont) + ".txt").c_str());

  glo_cont++;

  pthread_mutex_unlock(&mutex);
}

// Funcion para imprimir la informacion
void viewData(struct IPINFO *dataIp)
{

  int i = 0;

  cout << dataIp->nIp << "\t\t" << dataIp->nPackege << "   \t   " << dataIp->Ploss << "  \t   ";

  if (dataIp->Ploss <= dataIp->nPackege && dataIp->Ploss > 0)
  {
    cout << dataIp->nPackege - dataIp->Ploss << "\t   "
         << "UP" << endl;
  }
  else
  {
    cout << dataIp->nPackege - dataIp->Ploss << "\t   "
         << "DOWN" << endl;
  }

  i += 1;
}