#include "include/call_header.h"
std::string getDate()
{
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    const char * tc = ctime(&t);
    std::string str = std::string {tc};
    str.pop_back();
    return str;
}

void *runmin(void *varg) //min function
{
	///////////////////////////// declare all variable ///////////////////////////////////////
	std::string regId = "dhzyC5HLUVA:APA91bFDqRduJKR52ATJgi83zWbwLZkVM6fgCXMHviRXLggNxbcGdPOMzgrKrypaWauHbjh7hEqjcALy0qp4920eklmmrMpqxOnsxKX5WZunRp0XZ2EQar6J12g4JwgBp5hOOzo0U1WU";
	std::string title = "Periksa Alat";
	std::string message = " Tidak berfungsi";
	int handle, battery, rssi, data, temp, idalat, avail, humid, tempe;
	float awal = 0.0, OpTime, *q;
	//////////////////////////////////////////////////////////////////////////////////////////
	
	
	////////////////////////// open and flush serialport /////////////////////////////////////
	handle = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	
	////////////////////////////// prepare csv file //////////////////////////////////////////
	std::ofstream myfile;
	std::remove ("example.csv");
	myfile.open ("example.csv");
	// write the file headers
    myfile << "idalat" << "," << "data" << "," << "rssi" << "," << "battery" << "," << "datetime" << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////

	auto t1 = std::chrono::high_resolution_clock::now();
	while(1){
		/*
		//get status actuator every loop
		int *p;
		p = getStatus();
		printf("14= %d ", *(p+0));
		printf("15= %d ", *(p+1));
		printf("16= %d\n", *(p+2));
		*/
		
		//////////////////function to call every t seconds////////////////////////////////////
		auto t2 = std::chrono::high_resolution_clock::now();
		if((std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()) == 60){
			Jalan();
			
			/*
			temp = 5;
			q = hitung(awal, temp, 14);
			printf("uk adalah= %f\n" , *(q+0));
			printf("dur adalah= %f\n" , *(q+1));
			sendDataToServer(5, temp, *(q+0), 60, 14);
			publish(5, temp, uk, 60, 14);
			*/
			
			t1 = t2;		
		}
		//////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////// check serial data ////////////////////////////////////////
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		
		//////////////////////////////////////////////////////////////////////////////////////
		if(avail >= 1){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			humid = serialGetchar(handle) ;
			tempe = serialGetchar(handle) ;
			rssi = serialGetchar(handle) ;
			battery = serialGetchar(handle) ;
					
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", data);

			//////////////////////// write the needed data ///////////////////////////////
			myfile << idalat << "," << data << "," << rssi << "," << battery << "," << getDate() << std::endl;
			temp = data;
			//////////////////////////////////////////////////////////////////////////////
			
			q = hitung(awal, temp, 14);
			printf("uk adalah= %f\n" , *(q+0));
			printf("dur adalah= %f\n" , *(q+1));
			printf("hpsp adalah= %f\n" , *(q+2));
			
			double dur1, dur2;
			if( (*(q+0)) > 0 ){
				double tConst = (*(q+0));
				double dur = tConst * 1 * (*(q+1));
				OpTime = dur;
				printf("OpTime: %f\n" , dur);

				dur1 = dur/255;
				dur1 = (int)dur1;
				dur2 = dur - (dur1*255);
				printf("Konstanta: %f\n" , dur1);
				printf("Tambahan:  %f\n" , dur2);

				serialPutchar (handle, idalat);
				serialPutchar (handle, dur1);
				serialPutchar (handle, dur2);
				
				//publish(HPSp, temp, uk, OpTime, idalat);
				awal = temp;
				sendDataToServer((*(q+2)), temp, humid, tempe, (*(q+0)), OpTime, idalat);
				updateStatusAlat(rssi, battery, idalat, 1);
				/*
				message = std::to_string(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";		
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				*/
			}
			
			else{
				//publish(HPSp, temp, uk, OpTime, idalat);
				awal = temp;
				sendDataToServer((*(q+2)), temp, humid, tempe, (*(q+0)), OpTime, idalat);
				updateStatusAlat(rssi, battery, idalat, 0);
				/*
				message = std::to_string(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				*/
			}
		}
		///////////////////////If pump finish will get this data//////////////////////////
		if(avail == 2){
			idalat = serialGetchar(handle);
			data = serialGetchar(handle);
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", data);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//////////////////////////////////////////////////////////////////////////////////
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	myfile.close();

}



void generic_handler(struct evhttp_request *req, void *arg)
{
    struct evbuffer *buf;
    buf = evbuffer_new();
    if (buf == NULL)
        err(1, "failed to create response buffer");

    const char *param = evhttp_request_uri(req);
    std::string s = param;

	std::stringstream ss(s);
	std::string segment;
	std::vector<std::string> seglist;

	while(std::getline(ss, segment, '/'))
	{
		seglist.push_back(segment);
	}
	std::string param1 = seglist[1];
	std::string param2 = seglist[2];
	int uc1 = std::stoi( param1 );
	int uc2 = std::stoi( param2 );
	std::cout << "Convert" << param1 << std::endl;
	std::cout << "Convert" << param2 << std::endl;

    evbuffer_add_printf(buf, "Requested: %s\n", param);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);

    int handle2 = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle2);
	serialPutchar (handle2, uc1);
	serialPutchar (handle2, uc2);
	serialClose (handle2) ;
	
}

void *runmax(void *varg) //min function
{


    struct evhttp *httpd;
    event_init();
    httpd = evhttp_start("0.0.0.0", 5555);

    /* Set a callback for requests to "/specific". */
    /* evhttp_set_cb(httpd, "/specific", another_handler, NULL); */

    /* Set a callback for all other requests. */
    evhttp_set_gencb(httpd, generic_handler, NULL);

    event_dispatch();    /* Not reached in this code as it is now. */
    evhttp_free(httpd);

}


int main(){

	
	
	pthread_t tid1, tid2;
    printf("Before Threads\n");
    pthread_create(&tid1, NULL, runmin, (void*) "haha"); 
    pthread_create(&tid2, NULL, runmax, (void*) "haha");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
	

	return 0;
}
