#include "RPN.hpp"

int main(int c, char **v)
{
    try
    {
        if (c != 2)
            throw   std::logic_error("Error");
        RPN cal;
        cal.RPN_result(v[1]);
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;;
    }
}