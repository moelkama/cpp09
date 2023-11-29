#include <iostream>
#include <exception>
#include <fstream>
#include <map>
#include <algorithm>

class   btc
{
private:
    std::map<std::string, float>    DB;
    btc(const btc& other);
    btc&    operator=(const btc& other);
    void            check_date(std::string date, std::string bad);
    std::string     is_float(std::string str);
    void            read_line(std::string line);
public:
    btc();
    ~btc();

    void    read_input(std::string  infile);
};