static const char *URL_TOSERVER= "curl -X POST -H \"Authorization: 5d55ed73dda2730ec3e01a5f8c631966\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&humid=%f&temp=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.43.98/Sigap-Server/v1/data_sensor\"";
static const char *URL_NOTIFICATION= "curl -X POST -H \"Cache-Control: no-cache\" -H \"Postman-Token: 26d74e27-95c1-ec91-5c25-d7e14db55344\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'to=%s&title=%s&message=%s\' \"http://192.168.1.140/Sigap-Server/v1/sendsingle\"";
static const char *URL_UPDATEALAT= "curl -X PUT -H \"Authorization: 5d55ed73dda2730ec3e01a5f8c631966\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: 0f4cf5df-09ec-d9e4-2642-60ca3c950289\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'rssi=%f&battery=%f&idalat=%f\' \"http://192.168.1.116/Sigap-Server/v1/alatuser\"";

void sendDataToServer(double hpsp, double hpc, double humid, double temp, double uk, double opt, double idalat){
	char str[1000];
	sprintf(str, URL_TOSERVER, hpsp, hpc, humid, temp, uk, opt, idalat);
	puts(str);
	system(str);
	printf("\n");
}

void sendNotification(std::string to, std::string title, std::string message){
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