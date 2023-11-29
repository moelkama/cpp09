#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
private:
    std::stack<int> res;

    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
public:
    RPN();
    ~RPN();
    void    RPN_result(char *arg);
};

#endif
