#include <iostream>				// standar cout cin
#include <chrono>				// timer function
#include <stdio.h>				// standar printf scanf
#include <thread>				// multi threading
#include <fstream>				// save output file
#include <ctime>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <wiringSerial.h>		// komunikasi serial xbee
#include <mosquitto.h>			// mosquitto publish subscribe
#include <math.h>				// math function ex: pow()
#include <curl/curl.h>			// get data from api
#include <jsoncpp/json/json.h>	// decode json response

//must in bottom include//
#include <my_global.h>			// database connection
#include <mysql.h>				// database query
//////////////////////////

#include <event.h>
#include <evhttp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <err.h>
#include <pthread.h>