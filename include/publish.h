#define MQTT_HOSTNAME "localhost" 
#define MQTT_PORT 1883
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "test"

#define SERVER "192.168.43.98"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "sigap"

static const char *MQTT_PAYLOAD = "{\"hpsp\": %f, \"hpc\": %f, \"uk\": %f, \"optime\": %f, \"idalat\": %f}";
static const char *INSERT_QUERY = "INSERT INTO datasensor (id_alat, hpsp, hpc, uk, optime) VALUES (%f, %f, %f, %f, %f)";

void publish(double hpsp, double hpc, double uk, double optime, double idalat){
	std::string query;
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

	char text[1000];
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
        std::cout << "Connection Established Successfully......." << std::endl;
    }

    connect = mysql_real_connect(connect, SERVER, USERNAME, PASSWORD, DATABASE, 0,NULL,0);

    if (connect){
        std::cout << "Connection Established Successfully......." << std::endl;
    }
	char que[1000];
    //query = "INSERT INTO datasensor (id_alat) VALUES ('14')";
    sprintf (que, INSERT_QUERY, idalat, hpsp, hpc, uk, optime);
	std::cout << query << std::endl;
	if (mysql_query(connect, que)){
    //if (mysql_query(connect, query.c_str())){
        std::cout << "Success.... \n" << std::endl;
    }   

    mysql_close (connect);  
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	mosquitto_disconnect (mosq);
	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();
}