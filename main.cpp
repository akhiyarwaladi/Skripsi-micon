#include<iostream>
#include<wiringSerial.h>

using namespace std;

int main(){
	int handle, data;
	handle = serialOpen("/dev/ttyAMA0", 9600) ;
	while(1){
		data = serialGetchar(handle) ;
		cout << data << "\n";
	}
	return 0;
}
