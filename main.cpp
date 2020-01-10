#include "HashMap.hpp"
#include "inputs.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	bool debug = false;
	std::string entireInput;
	std::string command;
	std::string parameter1;
	std::string parameter2;
	std::string waste;
	HashMap loginSystem;

	while (true)
	{	
		std::getline(std::cin, entireInput);
		std::istringstream differentInputs(entireInput);
		differentInputs >> command >> parameter1 >> parameter2 >> waste;

		if (command == "QUIT")
		{
			break;
		}
		else if (waste != "")
		{
			std::cout << "INVALID" << std::endl;
		}
		// else if (command == "PRINT")
		// {
		// 	loginSystem.printBucketList();
		// }
		else if (command == "CREATE")
		{
			handleCreateCommand(command, parameter1, parameter2, loginSystem);
		}
		else if (command == "LOGIN" && parameter1 != "" && parameter2 != "")
		{
			handleLoginCommand(command, parameter1, parameter2, loginSystem);
		}
		else if (command == "REMOVE")
		{
			handleRemoveCommand(command, parameter1, parameter2, loginSystem);
		}
		else if (command == "CLEAR" && parameter1 == "" && parameter2 == "")
		{
			std::cout << "CLEARED" << std::endl;
			loginSystem.clearBucketList();
		}
		// moving onto debug commands
		else if (command == "DEBUG" and parameter1 == "ON")
		{
			// stopped working here
			if (debug == false)
			{
				debug = true;
				std::cout << "ON NOW" << std::endl;
			}
			else
			{
				std::cout << "ON ALREADY" << std::endl;
			}
		}
		else if (command == "DEBUG" and parameter1 == "OFF")
		{
			if (debug == true)
			{
				debug = false;
				std::cout << "OFF NOW" << std::endl;
			}
			else
			{
				std::cout << "OFF ALREADY" << std::endl;
			}
		}
		else if (command == "LOGIN" && parameter1 == "COUNT" && debug == true)
		{
			std::cout << loginSystem.size() << std::endl;
		}
		else if (command == "BUCKET" && parameter1 == "COUNT" && debug == true)
		{
			std::cout << loginSystem.bucketCount() << std::endl;
		}
		else if (command == "LOAD" && parameter1 == "FACTOR" && debug == true)
		{
			std::cout << loginSystem.loadFactor() << std::endl;
		}
		else if (command == "MAX" && parameter1 == "BUCKET" && parameter2 == "SIZE" && debug == true)
		{
			std::cout << loginSystem.maxBucketSize() << std::endl;
		}
		else
		{
			std::cout << "INVALID" << std::endl;
		}


		command = "";
		parameter1 = "";
		parameter2 = "";
		waste = "";
	}
	std::cout << "GOODBYE" << std::endl;

    return 0;
}

