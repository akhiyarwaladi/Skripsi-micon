using namespace std;
static const char *payload = "{"hpsp": %s, "hpc": %s, "uk": %s, "optime": %s, "idalat": %d}";

void publish(float hpsp, float hpc, float uk, float optime, int idalat){
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

	char text[100];
	sprintf (text, payload, hpsp, hpc, uk, optime, idalat);
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

    query = "INSERT INTO datasensor (id_alat, hpsp, hpc, uk, optime) VALUES('"+idalat+"', '"+hpsp+"', '"+hpc+", '"+uk+"', '"+optime+"')";

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