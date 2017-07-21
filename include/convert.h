std::string convertid(int id){

	std::string idnode;
	if (id == 14) idnode = "596b4265e19ddd256001d344";
	
	else if (id == 15) idnode = "596b6487e19ddd256001d347";
	else if (id == 16) idnode = "596b4288e19ddd256001d346";

	return idnode;
}

std::string convertidToInt(std::string id){

	std::string idnode;
	if (id == "596b4265e19ddd256001d344") idnode = "14";
	
	else if (id == "596b6487e19ddd256001d347") idnode = "15";
	else if (id == "596b4288e19ddd256001d346") idnode = "16";

	return idnode;
}

std::string getIpAddr(){
	std::string ipAddr;
	int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;
    
    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, "wifi0", IFNAMSIZ-1);
    
    ioctl(fd, SIOCGIFADDR, &ifr);
    
    close(fd);
    
    /* display result */
    //printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    ipAddr = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	return ipAddr;
}