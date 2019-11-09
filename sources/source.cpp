// Copyright 2018 Your Name <your_email>

#include "../include/header.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

/*std::string openFile(std::string name){
    //std::cout << std::endl <<" Please, get me a name : ";
    std::string line;

    std::ifstream in(name); // окрываем файл для чтения
    if (in.is_open())
    {
        std::cout << std::endl << " We get: " << std::endl;
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
        in.close();
        return line;
    }
    else
        return "NOT_FOUND";
     // закрываем файл

}*/

void newFile(std::string name, nlohmann::json json){
    name=name+"_reload.txt";
    std::ofstream out(name); //создать
    out << json << std::endl;
    out.close();
}