// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <header.hpp>
#include <json.h>





TEST(Json, Json1)
{
    std::string line =R"(
        {
            "lastname" : "Ivanov",
            "firstname" : "Ivan",
            "age" : 25,
            "islegal" : false,
            "marks" : [
                4,5,5,5,2,3
            ]
        }
    )";
    Json object = Json::parse(line);




    auto marks = std::any_cast<std::vector<std::any>>(object["marks"]);
//дальше не идёт
    std::cout<<"yes we there\n";


    ASSERT_EQ(std::any_cast<double>(marks[0]), 4);
    ASSERT_EQ(std::any_cast<double>(marks[1]), 5);
    ASSERT_EQ(std::any_cast<double>(marks[2]), 5);
    ASSERT_EQ(std::any_cast<double>(marks[3]), 5);
    ASSERT_EQ(std::any_cast<double>(marks[4]), 2);
    ASSERT_EQ(std::any_cast<double>(marks[5]), 3);

}

TEST(Json, Json2)
{
    Json object = Json::parse(R"(
        {
            "lastname" : "Ivanov",
            "address" : {
                "city" : "Moscow",
                "street" : "Vozdvijenka"
            }
        }
    )");


    auto address = std::any_cast<Json >(object["address"]);
    ASSERT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
    ASSERT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}


TEST(Json, stringToArray)//+
{
    std::string line = "1,2,3,345";
    std::vector <std::string> result1={"1","2","3","345"};
    std::vector <std::string> result2= Json::stringToArray(line);
    ASSERT_EQ(result1,result2);
}


TEST(Json, function3_2)//+
{
    std::string line1 = "true";
    ASSERT_EQ(std::any_cast<bool>( Json::function3_2(line1)), true);

    std::string line2 = "false";
    ASSERT_EQ(std::any_cast<bool>( Json::function3_2(line2)), false);


    std::string line3 = "97";
    ASSERT_EQ(std::any_cast<double>( Json::function3_2(line3)), 97.);

}

TEST(Json, function3_1)//+
{
    std::string line1 = R"( "true")";
    std::any result1 = Json::function3_1(line1);
    ASSERT_EQ(std::any_cast<std::string>(result1), "true");
}




TEST(Json, function1)//+
{
    std::string line1 = "{line,[123,1],123}";
    std::vector <std::string> result1 = Json::function1(line1);
    ASSERT_EQ(result1[0], "line");
    ASSERT_EQ(result1[1], "[123,1]");
    ASSERT_EQ(result1[2], "123");
}


TEST(Json, chechQuotes)//+
{
    std::string line1 = "{1,2,3,345}";
    ASSERT_EQ(Json::checkQuotes(line1), true);

    std::string line2 = "1,2,3,345}";
    ASSERT_EQ(Json::checkQuotes(line2), false);

    std::string line3 = "{1,2,3,345}}";
    ASSERT_EQ(Json::checkQuotes(line3), false);

    std::string line4 = "{{1,2,3,345}";
    ASSERT_EQ(Json::checkQuotes(line4), false);

    std::string line5 = "{{1,2,3,345}{...}}";
    ASSERT_EQ(Json::checkQuotes(line5), true);

}
TEST(Json, function2)//+
{
    std::string line1 = R"("lastname" : "Ivanov")";
    std::vector <std::pair< std::string, std::string>> result1 = Json::function2(line1);
    ASSERT_EQ(result1[0].first, R"("lastname")");
    ASSERT_EQ(result1[0].second, R"("Ivanov")");
}

TEST(Json, function2_2)//+
{
    std::string line1 = R"("lastname" : 23)";
    std::vector <std::pair< std::string, std::string>> result1 = Json::function2(line1);
    ASSERT_EQ(result1[0].first, R"("lastname")");
    ASSERT_EQ(result1[0].second, "23");
}

TEST(Json, ParseFile)
{
    auto object = Json::parseFile("../tests/test.txt");
    ASSERT_EQ( std::any_cast<std::string>(object["lastname"]), "Ivanov");
    ASSERT_EQ( std::any_cast<bool>(object["islegal"]), false);
    ASSERT_EQ( std::any_cast<double>(object["age"]), 25);

}
TEST(Json, ArrayFunc)
{
    std::string line = "[1,2,3,4]";
    std::any one = Json::arrayFunction(line);
    std::vector<std::any> temp_vector = std::any_cast<std::vector<std::any>>(one);
    ASSERT_EQ(std::any_cast<double>(temp_vector.at(0)), 1.);
}
