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
                Command cmd = cmds.at(i);
                if (cmd.cmd == "var")
                {
                    std::string name = cmd.params.at(0);
                    std::shared_ptr<Variable> var = std::make_shared<Variable>(name);
                    this->m_variables.insert(name, var);
                }
                else if (cmd.cmd == "letvar")
                {
                    std::string name1 = cmd.params.at(0);
                    std::string name2 = cmd.params.at(1);
                    Variable &var1 = *(this->m_variables.get_value(name1));
                    Variable &var2 = *(this->m_variables.get_value(name2));
                    var1.data = var2.data;
                }
                else if (cmd.cmd == "letval")
                {
                    std::string name = cmd.params.at(0);
                    std::string value = cmd.params.at(1);
                    Variable &var = *(this->m_variables.get_value(name));
                    var.data = parse_string(value);
                }
                else if (cmd.cmd == "printvar")
                {
                    std::string name = cmd.params.at(0);
                    Variable &var = *(this->m_variables.get_value(name));
                    std::cout << var.data;
                }
                else if (cmd.cmd == "printval")
                {
                    std::string value = cmd.params.at(0);
                    if (isNumberInt(value) || isNumberFloat(value))
                        std::cout << value;
                    else if (isString(value))
                        std::cout << parse_string(value);
                }
                else if(cmd.cmd == "pass")
                {
                    // do nothing
                }
                else if(cmd.cmd == "error")
                {
                    std::cout << std::endl << cmd.params.at(0) << std::endl;
                    terminate();
                }
                else
                {
                    std::cout << "Unknown command:\"" << cmd.cmd << "\"" << std::endl;
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
