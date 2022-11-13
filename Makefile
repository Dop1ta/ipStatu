#VARIABLES
ARCH = "archivo_listado_ips.txt" # $(OBJS)
BINARY = 2 # $(BINARY)


all: ipMain

ipMain: ipInfoThread.o
	g++ ipInfoThread.o -o ipInfoThread -lpthread  
	./ipInfoThread $(ARCH) $(BINARY)

ipInfoThread.o: ipInfoThread.cpp
	@g++ -c ipInfoThread.cpp 

clean:
	rm -f ipInfoThread *.o