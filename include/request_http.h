/*
static const char *URL_TOSERVER= "curl -X POST -H \"Authorization: 5d55ed73dda2730ec3e01a5f8c631966\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: c6054f6b-8f38-6630-f6da-1101ef4d3e59\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'hpsp=%f&hpc=%f&humid=%f&temp=%f&uk=%f&optime=%f&idalat=%f\' \"http://192.168.43.98/Sigap-Server/v1/data_sensor\"";
static const char *URL_NOTIFICATION= "curl -X POST -H \"Cache-Control: no-cache\" -H \"Postman-Token: 26d74e27-95c1-ec91-5c25-d7e14db55344\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'to=%s&title=%s&message=%s\' \"http://192.168.43.98/Sigap-Server/v1/sendsingle\"";
static const char *URL_UPDATEALAT= "curl -X PUT -H \"Authorization: 5d55ed73dda2730ec3e01a5f8c631966\" -H \"Cache-Control: no-cache\" -H \"Postman-Token: 0f4cf5df-09ec-d9e4-2642-60ca3c950289\" -H \"Content-Type: application/x-www-form-urlencoded\" -d \'rssi=%f&battery=%f&idalat=%f&status=%f\' \"http://192.168.43.98/Sigap-Server/v1/alatuser\"";
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

void updateStatusAlat(double rssi, double battery, double idalat, double status){
	char str[1000];
	sprintf(str, URL_UPDATEALAT, rssi, battery, idalat, status);
	puts(str);
	system(str);
	printf("\n");
}
*/
//static const char *BASE_IP		= "192.168.0.111";
static const char *BASE_URL		= "http://192.168.43.98:3000/api";

static const char *payToServer	= "{\r\n  \"device\":\"597206a1487a43110490c0b0\",\r\n  \"sensornode\":\"%s\",\r\n  \"setPoint\": %f,\r\n  \"uk\": %f,\r\n  \"opTime\": %f,\r\n  \"data\": {\r\n    \"humidity\": %f,\r\n    \"temperature\": %f,\r\n    \"waterlevel\": %f\r\n  },\r\n }";
static const char *payToNotif		= "title=%s&message=%s&deviceid=597206a1487a43110490c0b0";

static const char *url_updateNode	= std::string(std::string(BASE_URL) + "/sensornode/%s/updates").c_str();
static const char *payUpdateStatus	= "status=%f";
static const char *payUpdateNotif	= "notification=%f";

//static const char *url_updateIp 	= std::string(std::string(BASE_URL) + "/device/%s/updates").c_str();
//static const char *payUpdateIpAddr	= "webaddr=%s";

void DataToServer(std::string idnode, double humid, double temp, double waterlevel, double setPoint, double opTime, double uk){
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, std::string(std::string(BASE_URL)+"/dataset/create").c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: e0ba268f-43ca-644b-0cec-424219da7334");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str_DataToServer[1000] = "";
	sprintf(str_DataToServer, payToServer, idnode.c_str(), setPoint, uk, opTime, humid, temp, waterlevel);
	puts(str_DataToServer);

	//curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\r\n  \"device\":\"590e009c2476bf2dbca3e393\",\r\n  \"sensornode\":\"590e00f72476bf2dbca3e394\",\r\n\r\n  \"data\": {\r\n    \"humidity\": 40,\r\n    \"temperature\": 40,\r\n    \"waterlevel\": 5\r\n  },\r\n  \"sensortype\": [\r\n    \"590f9508d71b1b270c77dfe4\",\r\n    \"590f954bd71b1b270c77dfe7\",\r\n    \"590f9598d71b1b270c77dfe8\"\r\n  ]\r\n}");
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str_DataToServer);
	curl_easy_perform(hnd);
}


void UpdateStatus(std::string idnode, double status){
	
	char url_UpdateStatus[1000] = "";
	sprintf(url_UpdateStatus, url_updateNode, idnode.c_str());
	puts(url_UpdateStatus);


	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(hnd, CURLOPT_URL, url_UpdateStatus);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: 0abb0bfd-ef1f-ce14-655d-b33b956a6589");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str_UpdateStatus[1000] = "";
	sprintf(str_UpdateStatus, payUpdateStatus, status);
	puts(str_UpdateStatus);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str_UpdateStatus);
	curl_easy_perform(hnd);

}

void UpdateNotif(std::string idnode, double status){
	
	char url_UpdateNotif[1000] = "";
	sprintf(url_UpdateNotif, url_updateNode, idnode.c_str());
	puts(url_UpdateNotif);


	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(hnd, CURLOPT_URL, url_UpdateNotif);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: 0abb0bfd-ef1f-ce14-655d-b33b956a6589");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str_UpdateNotif[1000] = "";
	sprintf(str_UpdateNotif, payUpdateNotif, status);
	puts(str_UpdateNotif);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str_UpdateNotif);
	curl_easy_perform(hnd);

}


void Notification(std::string title, std::string message){

	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, std::string(std::string(BASE_URL) + "/notification/send").c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: 8d76e94d-8dce-9506-a301-f2594877953c");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str_Notification[1000] = "";
	sprintf(str_Notification, payToNotif, title.c_str(), message.c_str());
	puts(str_Notification);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str_Notification);
	curl_easy_perform(hnd);

}

// void UpdateIpAddr(std::string ipAddr){
// 	char url_UpdateIpAddr[1000] = "";
// 	sprintf(url_UpdateIpAddr, url_updateIp, "59677346b89f4c3ec40c6d3a");
// 	puts(url_UpdateIpAddr);

// 	CURL *hnd = curl_easy_init();

// 	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
// 	curl_easy_setopt(hnd, CURLOPT_URL, url_UpdateIpAddr);

// 	struct curl_slist *headers = NULL;
// 	headers = curl_slist_append(headers, "postman-token: 0abb0bfd-ef1f-ce14-655d-b33b956a6589");
// 	headers = curl_slist_append(headers, "cache-control: no-cache");
// 	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
// 	headers = curl_slist_append(headers, "authorization: 5d55ed73dda2730ec3e01a5f8c631966");
// 	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
// 	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

// 	char str_UpdateIpAddr[1000] = "";
// 	sprintf(str_UpdateIpAddr, payUpdateIpAddr, ipAddr.c_str());
// 	puts(str_UpdateIpAddr);

// 	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str_UpdateIpAddr);
// 	curl_easy_perform(hnd);

// }

