
#define MQTT_HOSTNAME "localhost" 
#define MQTT_PORT 1883
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "test"

#define SERVER "192.168.1.140"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "sigap"
static const char *payload = "{"hpsp": %f, "hpc": %f, "uk":%f, "optime":%f, "idalat":%f}";
void publish(float hpsp, float hpc, float uk, float optime, float idalat){
	struct mosquitto *mosq = NULL;
	 
	// Initialize the Mosquitto library
	mosquitto_lib_init();

	// Create a new Mosquito runtime instance with a random client ID,
	//  and no application-specific callback data.  
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

	int i;
	char text[100];

	sprintf (text, payload, hpsp, hpc, uk, optime, idalat);
	// Publish the message to the topic
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
        //cout << "Your Name is " << empFirstName << endl;
    }

    query = "INSERT INTO datasensor (id_alat, hpsp, hpc, uk, optime) VALUES('"+idalat+"', '"+hpsp+"', '"+hpc+", '"+uk+"', '"+optime+"')";

    cout << query << endl;

    if (mysql_query(connect, query.c_str())){
        cout << "Success.... \n" << endl;
    }   

    mysql_close (connect);


	// We need a short delay here, to prevent the Mosquito library being
	//  torn down by the operating system before all the network operations
	//  are finished.
	sleep (1);

	// Tidy up
	mosquitto_disconnect (mosq);
	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();
}