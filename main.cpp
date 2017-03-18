#include "include/call_header.h"
#define MQTT_HOSTNAME "localhost" 
#define MQTT_PORT 1883
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "test"

#define SERVER "192.168.1.142"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "sigap"

using namespace std;
static const char *URL_TOSERVER= "curl -X POST -H \"Authorization: ed7edb7931ff62ca7275630ddedfa617\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.1.140/SiPadat-Server/v1/data_sensor\"";
static const char *URL_NOTIFICATION= "curl -X POST -H \"Cache-Control: no-cache\" -H \"Postman-Token: 26d74e27-95c1-ec91-5c25-d7e14db55344\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'to=%s&title=%s&message=%s\' \"http://192.168.1.140/SiPadat-Server/v1/sendsingle\"";
static const char *URL_UPDATEALAT= "curl -X PUT -H \"Authorization: 5d55ed73dda2730ec3e01a5f8c631966\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: 0f4cf5df-09ec-d9e4-2642-60ca3c950289\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'rssi=%f&battery=%f&idalat=%f\' \"http://192.168.1.116/SiPadat-Server/v1/alatuser\""
static const char *MQTT_PAYLOAD = "{\"hpsp\": %f, \"hpc\": %f, \"uk\": %f, \"optime\": %f, \"idalat\": %f}";

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

void updateStatusAlat(double rssi, double battery, double idalat){
	char str[500];
	sprintf(str, URL_UPDATEALAT, rssi, battery, idalat);
	puts(str);
	system(str);
	printf("\n");
}

void publish(double hpsp, double hpc, double uk, double optime, double idalat){
	string query;
	struct mosquitto *mosq = NULL;
	mosquitto_lib_init();

	mosq = mosquitto_new (NULL, true, NULL);
	if (!mosq)
	{
		fprintf (stderr, "Can't initialize Mosquitto library\n");
		exit (-1);
	}

	mosquitto_username_pw_set (mosq, MQTT_USERNAME, MQTT_PASSWORD);

	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	int ret = mosquitto_connect (mosq, MQTT_HOSTNAME, MQTT_PORT, 0);
	if (ret)
	{
		fprintf (stderr, "Can't connect to Mosquitto server\n");
		exit (-1);
	}

	char text[500];
	sprintf (text, MQTT_PAYLOAD, hpsp, hpc, uk, optime, idalat);
	ret = mosquitto_publish (mosq, NULL, MQTT_TOPIC, strlen (text), text, 0, false);
	
	if (ret)
	{
		fprintf (stderr, "Can't publish to Mosquitto server\n");
		exit (-1);
	}
	
	MYSQL *connect;
    connect = mysql_init(NULL);

    if (connect){
        cout << "Connection Established Successfully......." << endl;
    }

    connect = mysql_real_connect(connect, SERVER, USERNAME, PASSWORD, DATABASE, 0,NULL,0);

    if (connect){
        cout << "Connection Established Successfully......." << endl;
    }

    query = "INSERT INTO datasensor (id_alat, hpsp, hpc, uk, optime) VALUES ('14', '20', '20', '20', '20')";
    cout << query << endl;

    if (mysql_query(connect, query.c_str())){
        cout << "Success.... \n" << endl;
    }   

    mysql_close (connect);
    
	sleep (1);

	mosquitto_disconnect (mosq);
	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();
}

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

int main(){

	int handle, volt, rssi, data, temp, idalat, avail;
	string regId = "ewpLKlPBYKc:APA91bGpaj3nJOh69cI5EPTob2tPoH5c65Vn6N3sjL5JmwX163oL_IAt0f-BbKA_K2Sc7LrDE_Xa7Jx_Leu7Ty08EskSvVECtzJzUs78T8PXtZYMGDn8ag9ZWPm3vyCuzY4AFxFQWBXm";
	string title = "Periksa Alat";
	string message = " Tidak berfungsi";
	float awal = 0.0, OpTime;
	handle = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle);
	while(1){
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		if(avail >= 4){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			rssi = serialGetchar(handle) ;
			volt = serialGetchar(handle) ;
			temp = data;
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", temp);
			printf("Signal Strength= %d\n", rssi);
			printf("Battery level= %d\n", volt);
			
			updateStatusAlat(rssi, battery, idalat);
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
				publish(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				message = IntToString(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				
				sleep(1);
			}
			
			else{
				awal = temp;
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				publish(HPSp, HPc[1], __Uk[1], OpTime, idalat);
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
