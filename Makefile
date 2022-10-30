#VARIABLES
ARCH = "archivo_listado_ips.txt" # $(OBJS)
BINARY = 2 # $(BINARY)


all: ipMain

ipMain: ipInfo.o
	g++ -o ipInfo ipInfo.o
	./ipInfo $(ARCH) $(BINARY)

ipInfo.o: ipInfo.cpp
	@g++ -c ipInfo.cpp -lpthread 

clean:
	rm -f ipInfo *.o