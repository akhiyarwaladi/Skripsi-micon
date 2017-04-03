#include "include/call_header.h"

int main(){

	// create a name for the file output
	std::string filename = "exampleOutput.csv";
	int handle, battery, rssi, data, temp, idalat, avail, *p;
	std::string regId = "ewpLKlPBYKc:APA91bGpaj3nJOh69cI5EPTob2tPoH5c65Vn6N3sjL5JmwX163oL_IAt0f-BbKA_K2Sc7LrDE_Xa7Jx_Leu7Ty08EskSvVECtzJzUs78T8PXtZYMGDn8ag9ZWPm3vyCuzY4AFxFQWBXm";
	std::string title = "Periksa Alat";
	std::string message = " Tidak berfungsi";
	float awal = 0.0, OpTime;
	handle = serialOpen("/dev/ttyACM0", 9600) ;
	serialFlush (handle);
	auto t1 = std::chrono::high_resolution_clock::now();
	
	std::ofstream myfile;
	std::remove ("example.csv");
	myfile.open ("example.csv");
	// write the file headers
    myfile << "idalat" << "," << "data" << "," << "rssi" << "," << "battery" << "," << "datetime" << std::endl;

	while(1){

		p = getStatus();
		printf("14= %d ", *(p+0));
		printf("15= %d ", *(p+1));
		printf("16= %d\n", *(p+2));

		auto t2 = std::chrono::high_resolution_clock::now();
		
		//function to call every t seconds
		if((std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()) == 5){
			Jalan();
			//temp = 5;
			//float uk = hitung(awal, temp, 14);
			//printf("uk adalah= %f\n" , uk);
			//sendDataToServer(5, temp, uk, 60, 14);
			t1 = t2;		
		}
		
		avail = serialDataAvail(handle);
		printf("Data Available= %d\n", avail);
		if(avail == 4){
			idalat = serialGetchar(handle) ;
			data = serialGetchar(handle) ;
			rssi = serialGetchar(handle) ;
			battery = serialGetchar(handle) ;
			// get date time now
			std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
			std::time_t t = std::chrono::system_clock::to_time_t(p);
			// write the needed data
			myfile << idalat << "," << data << "," << "rssi" << "," << "battery" << std::ctime(&t) << std::endl;
			temp = data;
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", temp);
			printf("Signal Strength= %d\n", rssi);
			printf("Battery level= %d\n", battery);
			
			/*
			updateStatusAlat(rssi, battery, idalat);
			float uk = hitung(awal, temp, idalat);
			float HPSp = 5.0;
			double dur1, dur2;
			if(uk>0){
				double tConst = uk;
				double dur = tConst*1*60;
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
				
				publish(HPSp, temp, uk, OpTime, idalat);
				awal = temp;
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				
				message = std::to_string(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";		
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			
			else{
				publish(HPSp, temp, uk, OpTime, idalat);
				awal = temp;
				//sendDataToServer(HPSp, HPc[1], __Uk[1], OpTime, idalat);
				
				message = std::to_string(idalat) + message;
				sendNotification(regId, title, message);
				message = " Tidak berfungsi";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			*/
		}
		if(avail == 2){
			idalat = serialGetchar(handle);
			data = serialGetchar(handle);
			printf("Id Alat= %d\n", idalat);
			printf("Data Received= %d\n", data);
			//updateStatusAlat(rssi, battery, idalat);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	myfile.close();
	
	return 0;
}
