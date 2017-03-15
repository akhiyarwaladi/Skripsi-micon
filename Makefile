all: main subscribe

OPTIONAL_LIBS=-lcrypto -lssl -lcares
LIBS=-lmosquitto -lpthread -lmysqlclient -lwiringPi
FLAGS=-Wall -s -I /usr/include/mysql

main: main.cpp
	g++ $(FLAGS) -o main main.cpp $(LIBS) $(OPTIONAL_LIBS) 

subscribe: subscribe.cpp
	g++ $(FLAGS) -o subscribe subscribe.cpp $(LIBS) $(OPTIONAL_LIBS) 

clean:
	rm -f *.o main subscribe
