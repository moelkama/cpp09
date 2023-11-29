#include "PmergeMe.hpp"

int main(int c, char **v)
{
    try
    {
        if (c < 2)
            throw std::runtime_error("Error : no numbers set yet!");
        clock_t         time;
        Serializer<std::vector<unsigned int > > merge1;
        Serializer<std::deque<unsigned int > >  merge2;
        for (int i = 1; i < c; i++)
        {
            for (unsigned int j = 0; v[i][j]; j++)
                if (!std::isdigit(v[i][j]))
                    throw std::runtime_error("Error : no numbers set yet!");
        }
        time = clock();
        for (int i = 1; i < c; i++)
            merge1.push(std::stoi(v[i]));
        std::cout<<"Before: ";
        merge1.display();
        merge1.sort();
        std::cout<<"After: ";
        merge1.display();
        std::cout<<"Time to process a range of "<<c - 1<<" elements with std::vector : "<<((float)clock() - time)/ 1000<<" us"<<std::endl;
        time = clock();
        for (int i = 1; i < c; i++)
            merge2.push(std::stoi(v[i]));
        merge2.sort();
        std::cout<<"Time to process a range of "<<c - 1<<" elements with std::deque : "<<((float)clock() - time)/ 1000<<" us"<<std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return (1);
    }
    return 0;
}