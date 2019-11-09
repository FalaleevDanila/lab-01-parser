//
// Created by Falaleev Danila UI8-33 on 03.09.2019.
//

#ifndef TEMPLATE_JSON_H
#define TEMPLATE_JSON_H


#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <string>


class Json {

    std::unordered_map<std::string, std::any> jsonValue;
    // std::vector <std::any> array;
public:
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s);

    Json();

    void push__back(std::pair<std::string, std::any> newJsonValue);

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any operator[](const std::string& key);

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any operator[](size_t index);

    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s);

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file);


//----------------------------------------------------------------------------------------------------------------------

    //проверяет существование пары кавычек
    static bool checkQuotes(const std::string& s);

    static std::any arrayFunction(std::string& line);

    static std::vector <std::string> stringToArray(std::string const &line);

    static std::vector <std::string> function1(std::string const &line);
    static std::vector <std::pair< std::string, std::string>> function2(std::string const& line);
    static std::string function3_1(std::string& line);
    static std::any function3_2(std::string& line);

};


#endif //TEMPLATE_JSON_H
