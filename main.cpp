#include "db.h"

#include <iostream>
#include <sstream>

#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>

void getUserInput(std::string& dirName, uint16_t& age, std::vector<std::string>& movies) {
	std::cout << "enter director's name: ";
	fflush(stdin);
	std::getline(std::cin, dirName);

	std::cout << "enter director's age: ";
	fflush(stdin);
	std::cin >> age;

	fflush(stdin);
	std::cout << "enter the movies: " << std::endl;
	std::string tmp;
	while (true) {
		std::getline(std::cin, tmp);
		if (tmp.empty())
			break;
			
		movies.push_back(tmp);
	}
}

void printChoices() {
	std::cout << "1. insert director" << std::endl;
	std::cout << "2. list all directors" << std::endl;
	std::cout << "3. find by name" << std::endl;
	std::cout << "4. exit" << std::endl;
}

int main() {
	mongocxx::instance instance{}; 
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);		

	DB db(client);

	std::string dirName;
	uint16_t age;
	std::vector<std::string> movies;

	std::string name;


	for (;;) {
		int choice{};
		std::cout << "Choose one of following: " << std::endl;
		printChoices();
		fflush(stdin);
		std::cin >> choice;

		switch(choice) {
			case 1:
				getUserInput(dirName, age, movies);
				db.insert(DirectorContext(dirName, age, movies));
				break;
			case 2:
				db.listAllDirectors();
				break;
			case 3:
				std::cin >> name;
				db.findByName(name);
				break;
			case 4:
				std::cout << "session finished" << std::endl;
				return 0;
			default: 
				std::cout << "illegal choice" << std::endl;
				break;
		}
	}
}
