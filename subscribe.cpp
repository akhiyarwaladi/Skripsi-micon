#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <mysql.h>
#include <my_global.h>
#include <string>

#define MQTT_HOSTNAME "localhost" 
#define MQTT_PORT 1883
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "test"

using namespace std;

void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	string query, pay;
	pay = (char *)message->payload;
	printf ("Got message: %s\n", pay.c_str());
	
}

int main (int argc, char **argv)
{
	struct mosquitto *mosq = NULL;
	mosquitto_lib_init();

	mosq = mosquitto_new (NULL, true, NULL);
	if (!mosq)
	{
		fprintf (stderr, "Can't init Mosquitto library\n");
		exit (-1);
	}

	// Set up username and password
	mosquitto_username_pw_set (mosq, MQTT_USERNAME, MQTT_PASSWORD);

	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	int ret = mosquitto_connect (mosq, MQTT_HOSTNAME, MQTT_PORT, 0);
	if (ret)
	{
		fprintf (stderr, "Can't connect to Mosquitto server\n");
		exit (-1);
	}

	ret = mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0);
	if (ret)
	{
		fprintf (stderr, "Can't publish to Mosquitto server\n");
		exit (-1);
	}

	// Specify the function to call when a new message is received
	mosquitto_message_callback_set (mosq, my_message_callback);

	// Wait for new messages
	mosquitto_loop_forever (mosq, -1, 1);

	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();

	return 0;
}