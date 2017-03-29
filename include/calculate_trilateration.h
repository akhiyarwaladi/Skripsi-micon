std::string data;
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{
    for (unsigned int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

double distance(double rssi)
{
	double distance = pow(10.0, ((-45+rssi)/(10*1.8)));
	return distance;
}

double calcPositionX(double d1, double d2, double d3){
	double x1 = 2.0, x2 = 8.0, x3 = 2.0;
	double y1 = 2.0, y2 = 8.0, y3 = 8.0;
	double a[10][10] = {0.0}, c[10][10] = {0.0};

	a[0][0] = (d1*d1 - d2*d2) - (x1*x1 - x2*x2) - (y1*y1 - y2*y2);
	a[0][1] = 2.0 * (y2 - y1);
	a[1][0] = (d1*d1 - d3*d3) - (x1*x1 - x3*x3) - (y1*y1 - y3*y3);
	a[1][1] = 2.0 * (y3 - y1);
	double detA	= (a[0][0]*a[1][1]) - (a[1][0]*a[0][1]);
	
	c[0][0] = 2.0 * (x2 - x1);
	c[0][1] = 2.0 * (y2 - y1);
	c[1][0] = 2.0 * (x3 - x1);
	c[1][1] = 2.0 * (y3 - y1);
	double detC	= (c[0][0]*c[1][1]) - (c[1][0]*c[0][1]);
	printf("detA= %g ", detA);
	printf("detC= %g\n", detC);

	double X = detA / detC;
	return X;

}

double calcPositionY(double d1, double d2, double d3){
	double x1 = 2.0, x2 = 8.0, x3 = 2.0;
	double y1 = 2.0, y2 = 8.0, y3 = 8.0;	
	double b[10][10] = {0.0}, c[10][10] = {0.0};

	b[0][0] = 2.0 * (x2 - x1);
	b[0][1] = (d1*d1 - d2*d2) - (x1*x1 - x2*x2) - (y1*y1 - y2*y2);
	b[1][0] = 2.0 * (x3 - x1);
	b[1][1] = (d1*d1 - d3*d3) - (x1*x1 - x3*x3) - (y1*y1 - y3*y3);
	double detB	= (b[0][0]*b[1][1]) - (b[1][0]*b[0][1]);

	c[0][0] = 2.0 * (x2 - x1);
	c[0][1] = 2.0 * (y2 - y1);
	c[1][0] = 2.0 * (x3 - x1);
	c[1][1] = 2.0 * (y3 - y1);

	double detC	= (c[0][0]*c[1][1]) - (c[1][0]*c[0][1]);
	printf("detB= %g ", detB);
	printf("detC= %g\n", detC);
	
	double Y = detB / detC;
	return Y;
}

void Jalan(){
	
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://172.29.144.175/Sigap-Server/v1/getalatuser");
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &writeCallback);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Authorization: 5d55ed73dda2730ec3e01a5f8c631966");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    curl_global_cleanup();
	
	Json::Value jsonData;
    Json::Reader jsonReader;
	jsonReader.parse(data, jsonData);
	
	//std::cout << jsonData.toStyledString() << std::endl;
	int rsatu = jsonData["tasks"][1]["rssi"].asInt();
	int rdua = jsonData["tasks"][2]["rssi"].asInt();
	int rtiga = jsonData["tasks"][3]["rssi"].asInt();
	
	printf("rssisatu= %d ", rsatu);
	printf("rssidua= %d ", rdua);
	printf("rssitiga= %d\n", rtiga);
	
	double satu = distance(rsatu);
	double dua = distance(rdua);
	double tiga = distance(rtiga);
	
	printf("satu= %g ", satu);
	printf("dua= %g ", dua);
	printf("tiga= %g\n", tiga);
		
	double X = calcPositionX(satu, dua, tiga);
	double Y = calcPositionY(satu, dua, tiga);

	printf("X= %g ", X);
	printf("Y= %g\n", Y);
}