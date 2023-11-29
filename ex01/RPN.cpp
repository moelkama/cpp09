#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    *this = other;
}

RPN&    RPN::operator=(const RPN& other)
{
    (void)other;
    return (*this);
}

RPN::~RPN()
{
}

void    RPN::RPN_result(char *arg)
{
    std::string RPN_characters = "0123456789+-*/ ";
    int a;
    int b;

    for (unsigned int i = 0; arg[i]; i++)
    {
        if (RPN_characters.find(arg[i]) == std::string::npos)
            throw   std::logic_error("Error");
        if (std::isdigit(arg[i]))
            res.push(arg[i] - 48);
        else if (!std::isspace(arg[i]))
        {
            if (res.size() < 2)
                throw   std::logic_error("Error");
            b = this->res.top();
            res.pop();
            a = this->res.top();
            res.pop();
            if (arg[i] == '+')
                res.push(a + b);
            else if (arg[i] == '-')
                res.push(a - b);
            else if (arg[i] == '*')
                res.push(a * b);
            else
            {
                if (b == 0)
                    throw   std::logic_error("division by 0");
                res.push(a / b);
            }
        }
    }
    if (res.size() != 1)
        throw   std::logic_error("Error");
    std::cout<<res.top()<<std::endl;
}