#include "Header.hpp"

namespace Good
{
    std::vector<std::string> loadStringFromFile(std::string filename)
    {
        std::vector<std::string> result;

        std::ifstream fin;
        fin.open(filename);
        if (fin.fail())
        {
            std::cout << "could not open file" << std::endl;
            return result;
        }

        std::string temp;
        while (std::getline(fin, temp))
        {
            result.push_back(temp);
        }

        fin.close();
        return result;
    }

    std::vector<std::string> splitString(std::string source)
    {
        std::stringstream sstr;
        sstr << source;

        std::vector<std::string> result;
        std::string temp;
        while (sstr >> temp)
        {
            result.push_back(temp);
        }

        return result;
    }

    void printAllCommands(std::vector<Command> cmds)
    {
        for (size_t i = 0; i < cmds.size(); i++)
        {
            Command cmd = cmds.at(i);
            printCommand(cmd);
        }
    }

    void printCommand(Command cmd)
    {
        std::cout << cmd.cmd << std::endl;
        if (cmd.params.size() > 0)
        {
            std::cout << "\t";
            for (size_t i = 0; i < cmd.params.size(); i++)
            {
                std::cout << "\"" << cmd.params.at(i) << "\" ";
            }
            std::cout << std::endl;
        }
    }

    template <typename T>
    std::string toString(T arg)
    {
        std::stringstream sstr;
        sstr << arg;
        return sstr.str();
    }
} // namespace Gpp
