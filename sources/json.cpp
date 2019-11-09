//
// Created by danf2 on 03.09.2019.
//

#include "../include/json.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

Json::Json(const std::string &s) {
    *this = parse(s);
}

bool Json::is_array() const {
    try{
        std::vector <std::any> mass =
                std::any_cast<std::vector <std::any>>(jsonValue);
    }
    catch(const std::bad_any_cast&){
        return false;
    }
    return true;
}

bool Json::is_object() const {
    try{
        std::unordered_map <std::string, std::any> object =
                std::any_cast<std::unordered_map <std::string, std::any>>(jsonValue);
    }
    catch(const std::bad_any_cast&){
        return false;
    }
    return true;
}


// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-объектом, генерируется исключение.
std::any  Json::operator[](size_t index) {

    if(this->is_array()) {
        auto object_f = std::any_cast<std::vector < std::any>>(jsonValue);
        return object_f[index];
    }
    else throw std::runtime_error("it is no massive");
}


// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-массивом, генерируется исключение.
std::any  Json::operator[](const std::string &key) {
    if(this->is_object()) {
        auto object_f = std::any_cast<std::unordered_map<std::string, std::any>>(jsonValue);
        std::any &out = object_f.find(key)->second;

        return out;
    }
    else throw std::runtime_error("it is no massive");
}

Json::Json() {}

void Json::push__back(std::pair<std::string, std::any> newJsonValue) {
    this->jsonValue.insert(newJsonValue);
}

Json Json::parse(const std::string &s){
    Json one;
    std::vector <std::string> both = function1(s);
    for(size_t i=0;i<both.size();i++){
        std::vector <std::pair< std::string, std::string>> json=function2(both[i]);
        for(size_t j=0;j<json.size();j++){
            std::pair <std::string, std::any> jPair;
            jPair.first=function3_1(json[j].first);
            jPair.second=function3_2(json[j].second);
            one.push__back(jPair);
        }
    }
    return one;
}

// разбиваем массив
std::vector <std::string> Json::stringToArray(std::string const &line){
    std::vector <std::string> one;
    std::string word;

    for(auto i=line.begin(); i!=line.end(); ++i){

        if(*i ==','){
            one.push_back(word);
            word="";
        }
        else word+=*i;
        if(i==line.end()-1){
            one.push_back(word);
            word="";
        }
    }
    return one;
}
//переписать

std::any Json::arrayFunction(std::string &line){ // расшифровываем элементы массива
    std::vector <std::any> one;
    std::string copy = line;
   /* for(auto i=copy.begin();i!=copy.end();++i){
        if(*i=='[') {
            copy.erase(i);
            break;
        }
    }*/
    auto i1 = copy.find_first_of('[');
    if (i1!=std::string::npos){
        copy.erase(i1,1);
    }
    auto i2 = copy.find_last_of(']');
    if (i2!=std::string::npos){
        copy.erase(i2,1);
    }

    std::vector <std::string> arrayString = Json::function1(copy);
    for(size_t i = 0; i < arrayString.size(); ++i){
        one.push_back(Json::function3_2(arrayString[i]));
    }
    return one;
}

// расшифровка функций

// расшифровываем значение ключа
//3_2

// для 1-го значения
//3_1

// разбиваем подстроки на подстроки(на значение:ключ)
//2

// разбиваем на подстроки(убираем запятые)
//1

bool Json::checkQuotes(const std::string &s) {
    int notPair=0;
    for(auto start = s.begin(); start != s.end(); ++ start){
        if(*start =='{')
            notPair++;
        else if(*start=='}')
            notPair--;
        if(notPair<0){
            return false;
        }
    }
    if(notPair==0) {
        return true;
    }
    return false;
}





Json Json::parseFile(const std::string &path_to_file) {
    std::ifstream in(path_to_file); // окрываем файл для чтения

    if (in.fail()) {
        throw std::runtime_error("Error");//проверка на наличие файла
    }
    std::string line(
            (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>()
    );//считываем
    return Json(line);
}

std::any Json::function3_2(std::string& line){ // расшифровываем значение ключа
    std::any one;
    if(line[0]==' '){
        line.erase(0,1);
    }
    for(auto i=line.begin(); i!=line.end(); ++i){
        if(*i=='{'){
            one = parse(line);
            break;
        }
        else if(*i=='['){
            one = arrayFunction(line);
            break;
        }
        else if(*i=='"'){
            one=function3_1(line);
        }
        else if(line=="true") {
            one=true;
            break;
        }
        else if(line=="false") {
            one=false;
            break;
        }
        else if(line=="null") {
            one = nullptr;
            break;
        }
        else  if(*i >='0' && *i<='9'){
            double number=0;
            while(*i>='0' && *i<='9' && i!=line.end()){
                number=number*10+(*i-'0');
                i++;
            }
            one = number;
            break;
        }
    }
    return one;
}

std::string Json::function3_1(std::string& line){ // для 1-го значения

    std::string newLine;
    for(auto i=line.begin(); i<line.end(); ++i) {

        if (*i == '"') {
            i++;
            while (i != line.end() && *i != '"') {
                newLine += *i;
                i++;
            }
        }
    }
    return newLine;
}

std::vector <std::pair< std::string, std::string>> Json::function2(std::string const& line){  // разбиваем подстроки на подстроки(на значение:ключ)
    bool flag = false;
    std::vector <std::pair< std::string, std::string>> one;
    std::pair< std::string, std::string> jPair;
    std::string word;
    for(auto i=line.begin(); i!=line.end(); ++i) {
        if(*i=='{' && flag== true){
            while(*i != '}') {
                word = word + *i;
                i++;
            }
            word+=*i;
            jPair.second = word;
            one.push_back(jPair);
            jPair.first="";
            jPair.second="";
            flag=false;
        }
        else if (*i == ':' || i==line.end()-1) {
            if (flag == false) {
                jPair.first = word;
                flag = true;
                word = "";
            }
            else if (flag == true) {

                word+=*i;
                jPair.second = word;
                one.push_back(jPair);
                flag = false;
                jPair.first="";
                jPair.second="";
                word = "";
            }
        }
        if(*i!=':' && *i!=' ')
            word += *i;

    }
    return one;
}

std::vector <std::string> Json::function1(std::string const &line){ // разбиваем на подстроки(убираем запятые)
    if(checkQuotes(line)){
        std::string copy = line;

        auto i1 = copy.find_first_of('{');
        if (i1!=std::string::npos){
            copy.erase(i1,1);
        }
        auto i2 = copy.find_last_of('}');
        if (i2!=std::string::npos){
            copy.erase(i2,1);
        }

        std::vector <std::string> one;
        std::string word;

        for(auto i=copy.begin(); i!=copy.end(); ++i){
            if(*i=='{'  && i!=copy.end()) {

                word += *i;
                i++;
                while (*i != '}') {
                    word += *i;
                    i++;
                }
                word += *i;


            }
            else if(*i=='['){
                do{
                    word+=*i;
                    i++;
                } while(*i!=']');

                if(*i==']')
                    word+=*i;

            }
            else if(*i==',' || i == copy.end()-1){
                if( i == copy.end()-1) word+=*i;
                one.push_back(word);
                word="";
            }
            else word+=*i;
        }

        return one;
    }
    else throw std::runtime_error("Error");
}

