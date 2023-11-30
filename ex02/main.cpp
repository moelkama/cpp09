#include "PmergeMe.hpp"

int main(int c, char **v)
{
    try
    {
        if (c < 2)
            throw std::runtime_error("Error : no numbers set!");
        merge_sort(c, v);
    }
    catch (const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return (1);
    }
    return 0;
}