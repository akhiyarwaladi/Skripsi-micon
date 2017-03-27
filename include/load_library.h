#include <iostream>
#include <chrono> // timer function
#include <stdio.h>
#include <unistd.h> //fungsi sleep
#include <thread> // multi threading
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <wiringSerial.h> //komunikasi serial xbee
#include <mosquitto.h>
#include <math.h>
#include <curl/curl.h> //get data from api
#include <jsoncpp/json/json.h> //decode json response

//must in bottom include//
#include <my_global.h>
#include <mysql.h>
//////////////////////////