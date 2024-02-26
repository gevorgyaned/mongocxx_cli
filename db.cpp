#include "db.h"

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

DB::DB(mongocxx::client& client) {
	db = client["mydata"];
	coll = db["test"];
}

mongocxx::stdx::optional<mongocxx::result::insert_one> DB::insert(DirectorContext director) {
	bsoncxx::builder::stream::document builder;
    builder << "name" << director.name
            << "age" << director.age;

    auto vecBuilder = builder << "movies" << bsoncxx::builder::stream::open_array;
    for (const auto& movie : director.movies) {
        vecBuilder << movie;
    }
    vecBuilder << bsoncxx::builder::stream::close_array;

    bsoncxx::document::value doc = builder << bsoncxx::builder::stream::finalize;

	std::cout << bsoncxx::to_json(doc.view()) << std::endl;
	auto res = coll.insert_one(doc.view());

	return res;
}

void DB::listAllDirectors() {
	auto cursor = coll.find({});

	for (const bsoncxx::document::view& document : cursor) {
    	std::cout << bsoncxx::to_json(document) << std::endl;
	}
}
 
void DB::findByName(std::string& name) {
	bsoncxx::builder::stream::document query{};
    query << "name" << name;

    auto cursor = coll.find(query.view());

	for (auto doc : cursor) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
	}
}
