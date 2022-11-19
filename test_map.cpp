#include <iostream>
#include <string>
#include "Map.hpp"

int main()
{
    Good::Map<std::string,std::string> map;
    map.insert("a","value1");
    map.insert("b","value2");
    std::cout << map.find_key("a") << std::endl;
    std::cout << map.contain_key("a") << std::endl;
    std::cout << map.get_value("a") << std::endl;
    return 0;
}