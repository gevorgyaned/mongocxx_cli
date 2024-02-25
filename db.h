#pragma once

#include "director.h"
#include <cstdint>
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>

class DB {
public:	
	DB(mongocxx::client& client);
	mongocxx::stdx::optional<mongocxx::result::insert_one> insert(DirectorContext director);
	void listAllDirectors();
	void findByName(std::string& name);
private:
	mongocxx::database db;
	mongocxx::collection coll;	
};

