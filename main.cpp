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
int main(){

	///////////////////////////// declare all variable ///////////////////////////////////
	std::string filename = "exampleOutput.csv";
	std::string regId = "ewpLKlPBYKc:APA91bGpaj3nJOh69cI5EPTob2tPoH5c65Vn6N3sjL5JmwX163oL_IAt0f-BbKA_K2Sc7LrDE_Xa7Jx_Leu7Ty08EskSvVECtzJzUs78T8PXtZYMGDn8ag9ZWPm3vyCuzY4AFxFQWBXm";
	std::string title = "Periksa Alat";
	std::string message = " Tidak berfungsi";
	int handle, battery, rssi, data, temp, idalat, avail, humid, tempe, *p;
	float awal = 0.0, OpTime, *q;
	//////////////////////////////////////////////////////////////////////////////////////
	
	
	////////////////////////// open and flush serialport ////////////////////////////////
	handle = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle);
	
	/////////////////////////////////////////////////////////////////////////////////////
	
	
	////////////////////////////// prepare csv file /////////////////////////////////////
	std::ofstream myfile;
	std::remove ("example.csv");
	myfile.open ("example.csv");
	// write the file headers
    myfile << "idalat" << "," << "data" << "," << "rssi" << "," << "battery" << "," << "datetime" << std::endl;
    /////////////////////////////////////////////////////////////////////////////////////
	
	auto t1 = std::chrono::high_resolution_clock::now();
	while(1){
		/*
		//get status actuator every loop
		p = getStatus();
		printf("14= %d ", *(p+0));
		printf("15= %d ", *(p+1));
		printf("16= %d\n", *(p+2));
		*/
		
		//function to call every t seconds
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
		
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		if(avail >= 1){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			humid = serialGetchar(handle) ;
			tempe = serialGetchar(handle) ;
			rssi = serialGetchar(handle) ;
			battery = serialGetchar(handle) ;
					
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", temp);

			// write the needed data
			myfile << idalat << "," << data << "," << rssi << "," << battery << "," << getDate() << std::endl;
			temp = data;
			
			q = hitung(awal, temp, 14);
			printf("uk adalah= %f\n" , *(q+0));
			printf("dur adalah= %f\n" , *(q+1));
			printf("hpsp adalah= %f\n" , *(q+2));
			
			double dur1, dur2;
			if( (*(q+0))>0 ){
				double tConst = (*(q+0));
				double dur = tConst*1*(*(q+1));
				OpTime = dur;
				printf("Durasi %f\n" , dur);

				dur1 = dur/255;
				dur1 = (int)dur1;
				dur2 = dur - (dur1*255);
				printf("Konstanta %f\n" , dur1);
				printf("Tambahan  %f\n" , dur2);

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
	return 0;
}
