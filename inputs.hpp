#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "HashMap.hpp"
#include <iostream>
#include <string>

void handleCreateCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem);
void handleLoginCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem);
void handleRemoveCommand(std::string command, std::string userName, std::string password, HashMap& loginSystem);

#endif
