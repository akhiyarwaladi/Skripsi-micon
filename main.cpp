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
	//////////////// initiate time counter //////////////
	auto a1 = std::chrono::high_resolution_clock::now();
	auto t1 = std::chrono::high_resolution_clock::now();
	/////////////////////////////////////////////////////

	///////////////////////////// declare all variable ///////////////////////////////////////
	std::string regId = "dhzyC5HLUVA:APA91bFDqRduJKR52ATJgi83zWbwLZkVM6fgCXMHviRXLggNxbcGdPOMzgrKrypaWauHbjh7hEqjcALy0qp4920eklmmrMpqxOnsxKX5WZunRp0XZ2EQar6J12g4JwgBp5hOOzo0U1WU";
	std::string title = "Periksa Alat";
	std::string message = " Tidak berfungsi";
	std::string idalatt;
	int dataReceive[5] = {0};
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

	while(1){
		/*
		//get status actuator every loop
		int *p;
		p = getStatus();
		printf("14= %d ", *(p+0));
		printf("15= %d ", *(p+1));
		printf("16= %d\n", *(p+2));
		*/
		
		///////////////////function to call every t seconds////////////////////////////////////
		auto t2 = std::chrono::high_resolution_clock::now();
		if((std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()) == 10){
			//Jalan();
			/*
			temp = 5;
			q = hitung(awal, temp, 14);
			printf("uk adalah= %f\n" , *(q+0));
			printf("dur adalah= %f\n" , *(q+1));
			printf("hpsp adalah= %f\n" , *(q+2));
			//sendDataToServer(5, temp, *(q+0), 60, 14);
			//publish(5, temp, uk, 60, 14);
			//DataToServer("590e00f72476bf2dbca3e394", 80, 90, 5, *(q+2), *(q+1), *(q+0));
			//UpdateStatus("590e00f72476bf2dbca3e394", 1);
			*/
			t1 = t2;

				
		}
		//////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////// check serial data ////////////////////////////////////////
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);

		if(avail <= 0){
			auto a2 = std::chrono::high_resolution_clock::now();
			dataReceive[0] += std::chrono::duration_cast<std::chrono::seconds>(a2-a1).count();
			dataReceive[1] += std::chrono::duration_cast<std::chrono::seconds>(a2-a1).count();
			dataReceive[2] += std::chrono::duration_cast<std::chrono::seconds>(a2-a1).count();
			a1 = a2;	
		}


		//////////////////////////////////////////////////////////////////////////////////////
		if(avail == 5){

			/////////////////////////////// GET all data from serial /////////////////////////////////

			idalat 		= serialGetchar(handle) ;
			data 		= serialGetchar(handle) ;
			humid 		= serialGetchar(handle) ;
			tempe 		= serialGetchar(handle) ;
			rssi 		= serialGetchar(handle) ;
			battery 	= 50 ;

			//////////////////////////////////////////////////////////////////////////////////////////
					
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", data);

			/////////////////////////////// store time data received //////////////////////////////////
			auto a2 = std::chrono::high_resolution_clock::now();
			if (idalat == 14){
				idalatt = "590e00f72476bf2dbca3e394";
				dataReceive[0]	= 0;
				dataReceive[1]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				dataReceive[2]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				a1 = a2;
			}

			else if(idalat == 15){
				idalatt = "590e19d1ac49692798cdab4c";
				dataReceive[0]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				dataReceive[1]	= 0;
				dataReceive[2]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				a1 = a2;
			}

			else if (idalat == 16){
				idalatt = "5930d241e733191d9836fb57";
				dataReceive[0]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				dataReceive[1]	+= std::chrono::duration_cast<std::chrono::seconds>(a2 - a1).count();
				dataReceive[2]	= 0;
				a1 = a2;
			} 

			///////////////////////////////////////////////////////////////////////////////////////////

			///////////////////////////////// write the needed data ///////////////////////////////////////
			myfile << idalat << "," << data << "," << rssi << "," << battery << "," << getDate() << std::endl;
			temp = data - 13;
			///////////////////////////////////////////////////////////////////////////////////////////////
			
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
				
				DataToServer(idalatt, humid, tempe, temp, *(q+2), *(q+1), *(q+0));
				awal = temp;
				UpdateStatus(idalatt, 1);
			}
			
			else{
				DataToServer(idalatt, humid, tempe, temp, *(q+2), OpTime, *(q+0));
				awal = temp;
				UpdateStatus(idalatt, 0);

			}
		}
		///////////////////////If pump finish will get this data//////////////////////////
		if(avail == 2){
			idalat = serialGetchar(handle);
			data = serialGetchar(handle);
			idalatt = convertid(idalat);
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", data);
			UpdateStatus(idalatt, 0);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		//////////////////////////////////////////////////////////////////////////////////
		}

		if (dataReceive[0] >= 60){

			message = "590e00f72476bf2dbca3e394" + message;
			Notification(title, message);
			message = " Tidak berfungsi";
			dataReceive[0] = 0;

		}
		else if (dataReceive[1] >= 60){
			message = "590e19d1ac49692798cdab4c" + message;
			Notification(title, message);
			message = " Tidak berfungsi";
			dataReceive[1] = 0;

		}
		else if (dataReceive[2] >= 60){
			message = "591fb531e576db31a4b6a504" + message;
			Notification(title, message);
			message = " Tidak berfungsi";
			dataReceive[2] = 0;

		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	myfile.close();
	void *retmin = NULL;
	return retmin;

}



void generic_handler(struct evhttp_request *req, void *arg)
{
	// this function to send command to actuator 
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

	std::string idalatt;
	idalatt = convertid(uc1);

	UpdateStatus(idalatt, uc2);
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

	void *retmin = NULL;
	return retmin;
}


int main(){

	
	
	pthread_t tid1, tid2;
    printf("Before Threads\n");
    pthread_create(&tid1, NULL, runmin, (void*) "haha"); 
    pthread_create(&tid2, NULL, runmax, (void*) "hihi");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
	

	return 0;
}
