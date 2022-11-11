#include <thread>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;
void buscarLetras (char *str) {
  char c[2];
  int cnt = 0;

  int stream = open ("archivo_listado_ips.txt", O_RDONLY);

  if (stream == -1) {
    cout << "Error al abrir archivo" << std::endl;
    terminate();
  }

  while (read(stream,c,1)) {
    if (strchr(str,c[0])) {
      cnt++;
      string t = "Encontró: " + (string ) str + "\n";
      cout << t;
      sleep(1);
    }
  }
  close (stream);
  
  // Para convertir un número en string.
  ostringstream oss;
  oss << cnt;
  string t = "Caracter: " + (string ) str + "[" + oss.str() + " ocurencias]" + "\n";
  cout << t;
}

int main(int argc, char *argv[]) {
  thread threads[argc - 1];
  int i = 0;

  /* Crea todos los hilos */
  for (i=0; i < argc - 1; i++) {
    threads[i] = thread(buscarLetras, argv[i+1]);
  }

  /* Para esperar por el término de todos los hilos */
  for (i=0; i< argc - 1; i++) {
    threads[i].join();
  }

  return 0;
}
