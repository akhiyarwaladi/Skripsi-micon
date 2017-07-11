std::string convertid(int id){

	std::string idnode;
	if (id == 14) idnode = "590e00f72476bf2dbca3e394";
	
	else if (id == 15) idnode = "590e19d1ac49692798cdab4c";
	else if (id == 16) idnode = "5930d241e733191d9836fb57";

	return idnode;
}

std::string convertidToInt(std::string id){

	std::string idnode;
	if (id == "590e00f72476bf2dbca3e394") idnode = 14;
	
	else if (id == "590e19d1ac49692798cdab4c") idnode = 15;
	else if (id == "5930d241e733191d9836fb57") idnode = 16;

	return idnode;
}