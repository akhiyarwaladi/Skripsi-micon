all: main subscribe

OPTIONAL_LIBS=-lcrypto -lssl -lcares
LIBS=-lmosquitto -lpthread -lmysqlclient -lwiringPi -lcurl -ljsoncpp -lpthread
FLAGS=-Wall -s -I /usr/include/mysql -std=c++11 -Wl,--no-as-needed  

main: main.cpp
	g++ $(FLAGS) -o main main.cpp $(LIBS) $(OPTIONAL_LIBS) 

subscribe: subscribe.cpp
	g++ $(FLAGS) -o subscribe subscribe.cpp $(LIBS) $(OPTIONAL_LIBS) 

clean:
	rm -f *.o main subscribe
