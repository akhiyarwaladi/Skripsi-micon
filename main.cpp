#include "include/call_header.h"

using namespace std;
static const char *URL_CURL_NEW= "curl -X POST -H \"Authorization: 2a80899620b2cf195d918d5716adc1c5\" -H \"Content-Type: application/x-www-form-urlencoded\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: d0e062b4-49ee-6255-5e05-324b1bad112f\" -d \'suhu=%f&ph=%f&do=%f&hasil=%f&idalat=40664b8af3ac490bb46fd49888c3ab9f\' \"http://172.18.88.11/SiPadat-Server/v1/data_sensor\"";
static const char *URL_CURL= "curl -X POST -H \"Authorization: ed7edb7931ff62ca7275630ddedfa617\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.1.139/SiPadat-Server/v1/data_sensor\"";
void sendDataToServer(double hpsp, double hpc, double uk, double opt, double idalat){
	char str[500];
	sprintf(str, URL_CURL, hpsp, hpc, uk, opt, idalat);
	puts(str);
	system(str);
	printf("\n");
}
int main(){
	//ios::sync_with_stdio(false);
	int handle, data, temp, idalat, avail;
	long val, sleepp;
	double OpTime;
	float awal = 0.0;
	handle = serialOpen("/dev/ttyAMA0", 9600) ;
	serialFlush (handle);
	while(1){
		avail = serialDataAvail(handle);
		cout << avail << "\n";
		if(avail >= 2){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			temp = data;
			printf("Received %d\n", temp);

			int n = 2;
			float Er[n], dEr[n];
			float HPSp = 5.0;
			float f1 = 0.83;
			float f2 = 1.00;
			float Um = 1.00;
			float __Uk[n];
			float HPc[n] = {awal, temp};

			double dur1, dur2, dur3;

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
				sleepp = (int)dur + 7;
				printf("Durasi %f\n" , dur);

				dur1 = dur/255;
				dur1 = (int)dur1;
				dur2 = dur - (dur1*255);
				printf("Konstanta %f\n" , dur1);
				printf("Tambahan  %f\n" , dur2);
				int dur4 = dur1;
				int dur5 = dur2;
				serialPutchar (handle, dur4);
				//cmd[0] = dur4;
				//write(file, cmd, 1);
				//cmd[0] = dur5;
				//write(file, cmd, 1);
				
				awal = temp;
				sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				//sleep(sleepp);
				//__Uk[1] = 0;
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				sleep(2);
			}
			
			else{
				awal = temp;
				sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				sleep(2);
			}
		}
		sleep(1);
	}
	return 0;
}
