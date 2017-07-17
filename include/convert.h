std::string convertid(int id){

	std::string idnode;
	if (id == 14) idnode = "596b4265e19ddd256001d344";
	
	else if (id == 15) idnode = "596b6487e19ddd256001d347";
	else if (id == 16) idnode = "596b4288e19ddd256001d346";

	return idnode;
}

std::string convertidToInt(std::string id){

	std::string idnode;
	if (id == "596b4265e19ddd256001d344") idnode = 14;
	
	else if (id == "596b6487e19ddd256001d347") idnode = 15;
	else if (id == "596b4288e19ddd256001d346") idnode = 16;

	return idnode;
}