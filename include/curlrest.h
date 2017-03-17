static const char *URL_TOSERVER= "curl -X POST -H \"Authorization: ed7edb7931ff62ca7275630ddedfa617\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.1.140/SiPadat-Server/v1/data_sensor\"";
static const char *URL_NOTIFICATION= "curl -X POST -H \"Cache-Control: no-cache\" -H \"Postman-Token: 26d74e27-95c1-ec91-5c25-d7e14db55344\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'to=%s&title=%s&message=%s\' \"http://192.168.1.140/SiPadat-Server/v1/sendsingle\"";
double sendDataToServer(double hpsp, double hpc, double uk, double opt, double idalat){
	char str[500];
	sprintf(str, URL_TOSERVER, hpsp, hpc, uk, opt, idalat);
	puts(str);
	system(str);
	printf("\n");
}

string sendNotification(string to, string title, string message){
	char str[1000];
	sprintf(str, URL_NOTIFICATION, to.c_str(), title.c_str(), message.c_str());
	puts(str);
	system(str);
	printf("\n");
}