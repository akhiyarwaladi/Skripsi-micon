#include "include/call_header.h"

using namespace std;

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

int main(){

	int handle,rssi, data, temp, idalat, avail;
	string regId = "ewpLKlPBYKc:APA91bGpaj3nJOh69cI5EPTob2tPoH5c65Vn6N3sjL5JmwX163oL_IAt0f-BbKA_K2Sc7LrDE_Xa7Jx_Leu7Ty08EskSvVECtzJzUs78T8PXtZYMGDn8ag9ZWPm3vyCuzY4AFxFQWBXm";
	string title = "Periksa Alat";
	string message = " Tidak berfungsi";
	float awal = 0.0, OpTime;
	handle = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle);
	while(1){
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		if(avail >= 3){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			rssi = serialGetchar(handle) ; 
			temp = data;
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", temp);
			printf("Signal Strength= %d\n", rssi);
			
			//uk1, uk2 = hitung(awal, temp);
			int n = 2;
			float Er[n], dEr[n];
			float HPSp = 5.0;
			float f1 = 0.83;
			float f2 = 1.00;
			float Um = 1.00;
			float __Uk[n];
			float HPc[n] = {awal, temp};
			double dur1, dur2;

			for (int i=0; i<n; i++){
				Er[i] = HPc[i]-HPSp;
				printf("Er %f\n" , Er[i]);
			}
			for (int i=0; i<n; i++){
				if (i==0) dEr[i] = Er[i];
				else if (i==10) dEr[10] = 0;
				else dEr[i] = Er[i]-Er[i-1];
				printf("dEr %f\n" , dEr[i]);
			}
			for (int i = 0; i < n; i++){
				float _theta = theta(f1, Er[i], dEr[i]);
				float _Dk = Dk(f1, Er[i], dEr[i]);
				float _mN = mN(_theta);
				float _mD = mD(_Dk, f2);
				float _Uk = Uk(_mN, _mD, Um);

				__Uk[i] = _Uk;
			}
			for (int i = 0; i < n; i++){
				printf("Uk %f\n" , __Uk[i]);
			}
		
			if(__Uk[1]>0){
				double time = __Uk[1];
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
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				//publish(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				message = IntToString(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				
				sleep(1);
			}
			
			else{
				awal = temp;
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				//publish(HPSp, HPc[1], __Uk[1], OpTime, idalat);
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
