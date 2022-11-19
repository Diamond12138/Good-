#include "Header.hpp"

namespace Good
{
    std::vector<Command> toCommands(std::vector<std::string> source)
    {
        std::vector<Command> result;
        for (size_t i = 0; i < source.size(); i++)
        {
            std::vector<std::string> cmds = splitString(source.at(i));
            if (cmds.size() != 0)
            {
                Command cmd;
                std::string first = cmds.at(0);
                if (first == "var")
                    cmd = parse_var(cmds);
                else if (first == "let")
                    cmd = parse_let(cmds);
                else if (first == "print")
                    cmd = parse_print(cmds);
                else if (first == "//" || first == "note")
                    cmd.cmd = "pass";
                else
                    cmd = generate_error("Unknown command:\"" + first + "\"");
                result.push_back(cmd);
            }
        }
        return result;
    }

    bool checkCmdType(std::vector<std::string> source, std::string type)
    {
        if (source.size() == 0)
        {
            return (std::string("pass") == type);
        }
        else
        {
            return (source.at(0) == type);
        }
    }

    bool checkCmdParamCount(std::vector<std::string> source)
    {
        return true;
    }

    Command parse_var(std::vector<std::string> source)
    {
        if (!checkCmdType(source, "var"))
            return generate_error("command type error");
        if (!checkCmdParamCount(source))
            return generate_error("command param count error");

        Command result;
        result.cmd = source.at(0);
        std::string param1 = source.at(1);

        if (isKeyword(param1))
            return generate_error("variable name cannot be a keyword");
        else if (isConstant(param1))
            return generate_error("variable name cannot be a constant");

        result.params.push_back(param1);
        return result;
    }

    Command parse_let(std::vector<std::string> source)
    {
        if (!checkCmdType(source, "let"))
            return generate_error("command type error");
        if (!checkCmdParamCount(source))
            return generate_error("command param count error");

        Command result;
        std::string param1 = source.at(1);
        std::string param2 = source.at(2);

        if (isNumberInt(param2) || isNumberFloat(param2) || isString(param2))
            result.cmd = "letval";
        else
            result.cmd = "letvar";

        if (isKeyword(param1))
            return generate_error("variable name cannot be a keyword");
        else if (isConstant(param1))
            return generate_error("variable name cannot be a constant");

        if (isKeyword(param2))
            return generate_error("target value cannot be a keyword");

        result.params.push_back(param1);
        result.params.push_back(param2);
        return result;
    }

    Command parse_print(std::vector<std::string> source)
    {
        if (!checkCmdType(source, "print"))
            return generate_error("command type error");
        if (!checkCmdParamCount(source))
            return generate_error("command param count error");

        Command result;
        std::string param1 = source.at(1);

        if (isConstant(param1))
            result.cmd = "printval";
        else
            result.cmd = "printvar";

        if (isKeyword(param1))
            return generate_error("variable name cannot be a keyword");

        result.params.push_back(param1);
        return result;
    }

    Command generate_error(std::string info)
    {
        Command result;
        result.cmd = "error";
        result.params.push_back(info);
        return result;
    }

    bool isKeyword(std::string source)
    {
        if (source == "var" ||
            source == "let" ||
            source == "print")
            return true;
        else
            return false;
    }

    bool isConstant(std::string source)
    {
        if (source.size() == 0)
            return false;

        if (isNumberInt(source) || isNumberFloat(source) || isString(source))
            return true;
        else
            return false;
    }

    bool isNumberInt(std::string source)
    {
        if (source.size() == 0)
            return false;

        char first = source.at(0);
        if (first > '0' && first < '9')
        {
            if (!isNumberFloat(source))
            {
                return true;
            }
        }
        return false;
    }

    bool isNumberFloat(std::string source)
    {
        if (source.size() == 0)
            return false;

        char first = source.at(0);
        if (first > '0' && first < '9')
        {
            if (source.find_first_of('.') != source.npos)
            {
                return true;
            }
        }
        else if (first == '.')
        {
            return true;
        }
        return false;
    }

    bool isString(std::string source)
    {
        if (source.size() < 2)
            return false;

        return (source.at(0) == '\"');
    }
} // namespace Good
