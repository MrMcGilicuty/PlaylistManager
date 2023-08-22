#pragma once
#include <string>
class Song
{
public:
	std::string name = "";
	Song* prev = nullptr;
	Song* next = nullptr;
};



