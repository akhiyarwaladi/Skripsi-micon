std::string dataStatus;
size_t writeCallbackStatus(char* buf, size_t size, size_t nmemb, void* up)
{
    for (unsigned int c = 0; c<size*nmemb; c++)
    {
        dataStatus.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

int * getStatus(){
	dataStatus = "";
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://192.168.43.98/Sigap-Server/v1/getalatuser");
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &writeCallbackStatus);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    curl_global_cleanup();
	
	Json::Value jsonData;
    Json::Reader jsonReader;
	jsonReader.parse(dataStatus, jsonData);
	
	//std::cout << jsonData.toStyledString() << std::endl;
	int rsatu = jsonData["tasks"][1]["status"].asInt();
	int rdua = jsonData["tasks"][2]["status"].asInt();
	int rtiga = jsonData["tasks"][3]["status"].asInt();

	static int stat[5];
	stat[0] = rsatu;
	stat[1] = rdua;
	stat[2] = rtiga;
	
	return stat;
}