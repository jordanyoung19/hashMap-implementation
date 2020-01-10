#include <iostream>
#include <string>
#include "HashMap.hpp"

void handleCreateCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem)
{

	if (userName == "" || password == "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else if (loginSystem.contains(userName))
	{
		std::cout << "EXISTS" << std::endl;
	}
	else
	{
		loginSystem.add(userName, password);
		std::cout << "CREATED" << std::endl;
	}
}

void handleLoginCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem)
{
	if (userName == "" || password == "")
	{
		std::cout << "INVALID" << std::endl; 
	}
	else if (!loginSystem.contains(userName))
	{
		std::cout << "FAILED" << std::endl;
	}
	else if (loginSystem.value(userName) == password)
	{
		std::cout << "SUCCEEDED" << std::endl;
	}
	else
	{
		std::cout << "FAILED" << std::endl;
	}
}

void handleRemoveCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem)
{
	if (userName == "" || password != "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else if (loginSystem.contains(userName))
	{
		loginSystem.remove(userName);
		std::cout << "REMOVED" << std::endl;
	}
	else
	{
		std::cout << "NONEXISTANT"  << std::endl;
	}
}