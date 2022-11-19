#include <iostream>
#include <string>
#include "Header.hpp"
#include "Utils.cpp"
#include "Map.hpp"

int main()
{
    /*Good::Map<std::string,std::string> map;
    map.insert("a","value1");
    map.insert("b","value2");
    std::cout << map.find_key("a") << std::endl;
    std::cout << map.contain_key("a") << std::endl;
    std::cout << map.get_value("a") << std::endl;*/

    std::cout << Good::toString(666," ",666) << std::endl;
    return 0;
}