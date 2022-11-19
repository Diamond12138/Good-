#include "Header.hpp"

namespace Good
{
    void Executer::execute(std::vector<Command> cmds)
    {
        if (cmds.size() != 0)
        {
            this->is_running = true;
            for (size_t i = 0; i < cmds.size() && this->is_running; i++)
            {
                std::cout << i <<std::endl;
                Command cmd = cmds.at(i);
                if (cmd.cmd == "var")
                {
                    std::string name = cmd.params.at(1);
                    std::string type = cmd.params.at(0);

                    std::shared_ptr<Variable> var = std::make_shared<Variable>(name, type);

                    this->m_variables.insert(name, var);
                }
                else if (cmd.cmd == "letval")
                {
                    std::string name = cmd.params.at(0);
                    std::string value = cmd.params.at(1);
                    Variable &var = *(this->m_variables.get_value(name));

                    if (var.type == "int")
                    {
                        if (isNumberInt(value) || isNumberFloat(value))
                            var.data->as_int = std::stoi(value);
                        else if (isString(value))
                            var.data->as_int = std::stoi(parse_string(value));
                    }
                    else if (var.type == "float")
                    {
                        if (isNumberInt(value) || isNumberFloat(value))
                            var.data->as_float = std::stof(value);
                        else if (isString(value))
                            var.data->as_float = std::stof(parse_string(value));
                    }
                    else if (var.type == "string")
                    {
                        var.data->as_string = parse_string(value);
                    }
                }
                else if (cmd.cmd == "printvar")
                {
                    std::string name = cmd.params.at(0);
                    Variable &var = *(this->m_variables.get_value(name));

                    if (var.type == "int")
                    {
                        std::cout << var.data->as_int;
                    }
                    else if (var.type == "float")
                    {
                        std::cout << var.data->as_float;
                    }
                    else if (var.type == "string")
                    {
                        std::cout << var.data->as_string;
                    }
                }
            }
            this->is_running = false;
        }
    }

    void Executer::terminate()
    {
        this->is_running = false;
    }

    std::string Executer::parse_string(std::string source)
    {
        std::string result;
        if (isString(source))
        {
            std::stringstream sstr;
            size_t in_string = true;
            for (size_t i = 1; i < source.size(); i++)
            {
                char ch = source.at(i);
                if (!in_string)
                {
                    this->throw_bad_string(source);
                }
                else if (ch == '\\')
                {
                    char next = source.at(i + 1);
                    if (next == 'n')
                    {
                        sstr << '\n';
                    }
                    else if (next == '\"')
                    {
                        sstr << '\"';
                    }
                    else if (next == '\'')
                    {
                        sstr << '\'';
                    }
                    else
                    {
                        this->throw_bad_string(source);
                    }
                    i++;
                }
                else if (ch == '\"')
                {
                    in_string = false;
                }
                else
                {
                    sstr << ch;
                }
            }
            result = sstr.str();
        }
        else
        {
            this->throw_bad_string(source);
        }
        return result;
    }

    void Executer::throw_bad_string(std::string source)
    {
        std::cout << "Bad string:\"" << source << "\"" << std::endl;
        this->terminate();
    }
} // namespace Good
