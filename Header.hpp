#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <memory>
#include "Map.hpp"

namespace Good
{
    struct Variable;
    struct Command;
    struct Executer;

    // in Utils.cpp

    std::vector<std::string> loadStringFromFile(std::string filename);
    std::vector<std::string> splitString(std::string source);
    void printAllCommands(std::vector<Command> cmds);
    void printCommand(Command cmd);
    std::string toString();
    template <typename T>
    std::string toString(T arg);
    template <typename T,typename... Ts>
    std::string toString(T arg,Ts... args);

    // in Good.hpp

    struct Variable
    {
        std::string name;
        std::string data;

        Variable(std::string n, std::string d = std::string()) : name(n), data(d) {}
        ~Variable() {}
    };

    struct Command
    {
        Command(std::string c = "pass") : cmd(c) {}
        std::string cmd;
        std::vector<std::string> params;
    };

    // command tip
    // pass : pass
    // error (info) : error "something"
    // var (name) : var a
    // letvar (name) (from) : let a a
    // letval (name) (value) : let a 10
    // printvar (name) : print a
    // printval (type) (value) : print 10

    std::vector<Command> toCommands(std::vector<std::string> source);
    bool checkCmdType(std::vector<std::string> source, std::string type);
    // without effect
    bool checkCmdParamCount(std::vector<std::string> source);
    Command parse_var(std::vector<std::string> source);
    Command parse_let(std::vector<std::string> source);
    Command parse_print(std::vector<std::string> source);
    Command generate_error(std::string info);
    bool isKeyword(std::string source);
    bool isConstant(std::string source);
    bool isNumberInt(std::string source);
    bool isNumberFloat(std::string source);
    bool isString(std::string source);

    // in Executer.cpp

    class Executer
    {
    public:
        Map<std::string, std::shared_ptr<Variable>> m_variables;
        bool is_running = false;

    public:
        void execute(std::vector<Command> cmds);
        void terminate();
        std::string parse_string(std::string source);
        void throw_bad_string(std::string source);
    };
} // namespace Good
