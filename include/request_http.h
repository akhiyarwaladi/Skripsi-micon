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
static const char *BASE_URL		= "http://192.168.31.192:3000/api";
static const char *payToServer	= "{\r\n  \"device\":\"590e009c2476bf2dbca3e393\",\r\n  \"sensornode\":\"%s\",\r\n  \"setPoint\": %f,\r\n  \"uk\": %f,\r\n  \"opTime\": %f,\r\n  \"data\": {\r\n    \"humidity\": %f,\r\n    \"temperature\": %f,\r\n    \"waterlevel\": %f\r\n  },\r\n  \"sensortype\": [\r\n    \"590f9508d71b1b270c77dfe4\",\r\n    \"590f954bd71b1b270c77dfe7\",\r\n    \"590f9598d71b1b270c77dfe8\"\r\n  ]\r\n}";
static const char *payUpdate	= "device=590e009c2476bf2dbca3e393&status=%f";
static const char *payToNotif 	= "title=%s&message=%s";
static const char *url 			= std::string(std::string(BASE_URL) + "/sensornode/%s/update").c_str();


void DataToServer(std::string idnode, double humid, double temp, double waterlevel, double setPoint, double opTime, double uk){
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, std::string(std::string(BASE_URL)+"/dataset/create").c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: e0ba268f-43ca-644b-0cec-424219da7334");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str[1000];
	sprintf(str, payToServer, idnode.c_str(), setPoint, uk, opTime, humid, temp, waterlevel);
	puts(str);

	//curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\r\n  \"device\":\"590e009c2476bf2dbca3e393\",\r\n  \"sensornode\":\"590e00f72476bf2dbca3e394\",\r\n\r\n  \"data\": {\r\n    \"humidity\": 40,\r\n    \"temperature\": 40,\r\n    \"waterlevel\": 5\r\n  },\r\n  \"sensortype\": [\r\n    \"590f9508d71b1b270c77dfe4\",\r\n    \"590f954bd71b1b270c77dfe7\",\r\n    \"590f9598d71b1b270c77dfe8\"\r\n  ]\r\n}");
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str);
	curl_easy_perform(hnd);
}


void UpdateStatus(std::string idnode, double status){
	
	
	char ur[1000];
	sprintf(ur, url, idnode.c_str());
	puts(ur);


	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(hnd, CURLOPT_URL, ur);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "postman-token: 0abb0bfd-ef1f-ce14-655d-b33b956a6589");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "x-snow-token: SECRET_API_KEY");
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str[1000];
	sprintf(str, payUpdate, status);
	puts(str);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str);
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
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	char str[1000];
	sprintf(str, payToNotif, title.c_str(), message.c_str());
	puts(str);

	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str);
	curl_easy_perform(hnd);
}

