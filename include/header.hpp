// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <string>
#include <nlohmann/json.hpp>

std::string openFile(std::string);

void newFile(std::string name, nlohmann::json json);


#endif // INCLUDE_HEADER_HPP_
