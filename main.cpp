#include "include/call_header.h"

using namespace std;
static const char *URL_TOSERVER= "curl -X POST -H \"Authorization: ed7edb7931ff62ca7275630ddedfa617\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.1.140/SiPadat-Server/v1/data_sensor\"";
static const char *URL_NOTIFICATION= "curl -X POST -H \"Cache-Control: no-cache\" -H \"Postman-Token: 26d74e27-95c1-ec91-5c25-d7e14db55344\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'to=%s&title=%s&message=%s\' \"http://192.168.1.140/SiPadat-Server/v1/sendsingle\"";

void sendDataToServer(double hpsp, double hpc, double uk, double opt, double idalat){
	char str[500];
	sprintf(str, URL_TOSERVER, hpsp, hpc, uk, opt, idalat);
	puts(str);
	system(str);
	printf("\n");
}

void sendNotification(string to, string title, string message){
	char str[1000];
	sprintf(str, URL_NOTIFICATION, to.c_str(), title.c_str(), message.c_str());
	puts(str);
	system(str);
	printf("\n");
}

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

int main(){
	int handle, data, temp, idalat, avail;
	string regId = "ewpLKlPBYKc:APA91bGpaj3nJOh69cI5EPTob2tPoH5c65Vn6N3sjL5JmwX163oL_IAt0f-BbKA_K2Sc7LrDE_Xa7Jx_Leu7Ty08EskSvVECtzJzUs78T8PXtZYMGDn8ag9ZWPm3vyCuzY4AFxFQWBXm";
	string title = "Periksa Alat";
	string message = " Tidak berfungsi";
	float awal = 0.0, OpTime, uk1, uk2;
	handle = serialOpen("/dev/ttyAMA0", 9600) ;
	serialFlush (handle);
	while(1){
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		if(avail >= 2){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			temp = data;
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", temp);
			
			uk1, uk2 = hitung(awal, temp);
			if(uk2>0){
				double time = uk2;
				double dur = time*1*60;
				OpTime = dur;
				printf("Durasi %f\n" , dur);

				dur1 = dur/255;
				dur1 = (int)dur1;
				dur2 = dur - (dur1*255);
				printf("Konstanta %f\n" , dur1);
				printf("Tambahan  %f\n" , dur2);

				serialPutchar (handle, idalat);
				serialPutchar (handle, dur1);
				serialPutchar (handle, dur2);
				
				awal = temp;
				sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				message = IntToString(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				
				sleep(1);
			}
			
			else{
				awal = temp;
				sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				message = IntToString(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				sleep(1);
			}
		}
		sleep(1);
	}
	return 0;
}
