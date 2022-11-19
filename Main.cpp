#include <iostream>
#include "Header.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string filename = argv[1];
        /*std::cout << filename << std::endl;

        std::cout << "----------" << std::endl;*/

        std::vector<Good::Command> commands = Good::toCommands(Good::loadStringFromFile(filename));
        //Good::printAllCommands(commands);

        //std::cout << "----------" << std::endl;

        Good::Executer exec;
        exec.execute(commands);

        /*std::cout << "----------" << std::endl;
        std::cout << exec.parse_string("a") << std::endl;
        std::cout << exec.m_variables.contain_key("a") << std::endl;*/
    }
    return 0;
}