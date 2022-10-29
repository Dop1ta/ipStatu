#VARIABLES
OBJS = ipInfo.o # $(OBJS)
BINARY = ipInfo # $(BINARY)


all: ipMain

ipMain: ipInfo.o
	g++ -o ipInfo ipInfo.o
	./ipInfo $(foo) $(foo2)

ipInfo.o: ipInfo.cpp
	@g++ -c ipInfo.cpp -lpthread 

clean:
	rm -f ipInfo *.o