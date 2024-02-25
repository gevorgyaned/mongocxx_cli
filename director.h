#pragma once

#include <iostream>
#include <vector>

struct DirectorContext {
	DirectorContext(std::string& _name, uint16_t& _age, std::vector<std::string>& _movies)
		: name(_name), age(_age), movies(_movies) {};

	std::string name;
	std::vector<std::string> movies;
	uint16_t age;
};
