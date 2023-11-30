#include "PmergeMe.hpp"
#include <sys/time.h>

int main(int c, char **v)
{
    try
    {
        if (c < 2)
            throw std::runtime_error("Error : no numbers set yet!");
        PmergeMe<std::vector<unsigned int > > merge1;
        PmergeMe<std::deque<unsigned int > >  merge2;
        timeval start;
        timeval end;
        double  time;
        for (int i = 1; i < c; i++)
        {
            for (unsigned int j = 0; v[i][j]; j++)
                if (!std::isdigit(v[i][j]))
                    throw std::runtime_error("Error : no numbers set yet!");
        }
        gettimeofday(&start, NULL);
        for (int i = 1; i < c; i++)
            merge1.push(std::stoi(v[i]));
        std::cout<<"Before: ";
        merge1.display();
        merge1.sort();
        std::cout<<"After: ";
        merge1.display();
        gettimeofday(&end, NULL);
        time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - end.tv_usec);
        std::cout<<"Time to process a range of "<<c - 1<<" elements with std::vector : "<<time<<" us"<<std::endl;
        gettimeofday(&start, NULL);
        for (int i = 1; i < c; i++)
            merge2.push(std::stoi(v[i]));
        merge2.sort();
        gettimeofday(&end, NULL);
        time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - end.tv_usec);
        std::cout<<"Time to process a range of "<<c - 1<<" elements with std::deque : "<<time<<" us"<<std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return (1);
    }
    return 0;
}