#include <utility>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sys/time.h>

template    <typename T>
class PmergeMe
{
private:
    std::vector<std::pair<unsigned int, unsigned int> > pairs;
    std::pair<unsigned int, bool>   last;
    T   merge;
    T   largest;
    T   grandest;
    PmergeMe(const PmergeMe& other)
    {
        *this = other;
    }
    PmergeMe& operator=(const PmergeMe& other)
    {
        (void)other;
        return (*this);
    }
public:
    void    to_pairs()
    {
        typename T::iterator  it;
        typename T::iterator  eit;

        it = merge.begin();
        eit = merge.end();
        while (it != eit && it != eit - 1)
            pairs.push_back(std::pair<unsigned int, unsigned int>(*(it++), *(it++)));
        if (it != eit)
        {
            last.first = *it;
            last.second = true;
        }
    }
    void    sort_pairs()
    {
        std::vector<std::pair<unsigned int, unsigned int> >::iterator pairs_it;
        std::vector<std::pair<unsigned int, unsigned int> >::iterator pairs_eit;

        pairs_it = pairs.begin();
        pairs_eit = pairs.end();
        while (pairs_it != pairs_eit)
        {
            if (pairs_it->first > pairs_it->second)
                std::swap(pairs_it->first, pairs_it->second);
            largest.insert(lower_bound(largest.begin(), largest.end(), pairs_it->first), pairs_it->first);
            grandest.push_back(pairs_it->second);
            pairs_it++;
        }
    }
    void    sort()
    {
        typename T::iterator  it;
        typename T::iterator  eit;

        to_pairs();
        sort_pairs();
        it = grandest.begin();
        eit = grandest.end();
        while (it != eit)
        {
            largest.insert(lower_bound(largest.begin(), largest.end(), *it), *it);
            it++;
        }
        if (last.second)
            largest.insert(lower_bound(largest.begin(), largest.end(), last.first), last.first);
        merge.swap(largest);
    }
    void    push(unsigned int val)
    {
        merge.push_back(val);
    }
    void    display() const
    {
        typename T::const_iterator     it;
        typename T::const_iterator     eit;

        it = merge.begin();
        eit = merge.end();
        while (it != eit)
        {
            std::cout<<*(it++);
            if (it != eit)
                std::cout<<" ";
        }
        std::cout<<std::endl;
    }
    PmergeMe()
    {
        last.second = false;
    }
    ~PmergeMe(){}
};

void    merge_sort(int c, char **v);