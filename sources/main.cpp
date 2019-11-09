//
// Created by danila on 01.10.2019.
//
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "../include/header.hpp"



int main(){
    std::string way;
    std::cout << " Get me a way:";
    std::cin>> way;

    // Serialize
    nlohmann::json json;
    std::ifstream{way} >> json;

    // Проверка
    if (!json.is_array()) {
        std::cout << "Input JSON is not an array\n";
        return 1;
    }
    if (json.size() != 3) {
        std::cout << "Input JSON array size is not 3\n";
        return 1;
    }
    if (!(json[0].size() == json[1].size() && json[1].size() == json[2].size())) {
        std::cout << "Input JSON nested array sizes are not equal\n";
        return 1;
    }

    // Processing
    nlohmann::json outJson;
    for (size_t i = 0; i < json[0].size(); i++) {
        outJson.push_back(
                nlohmann::json{
                        {"ticker", json[0][i]},
                        {"id", json[1][i]},
                        {"description", json[2][i]},
                }
        );
    }

    newFile(way, outJson);

    return 0;
}