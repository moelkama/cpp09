#include "BitcoinExchange.hpp"

int main(int c, char **v)
{
    try
    {
        if (c != 2)
            throw   std::logic_error("Error: could not open file.");
        btc bitcoin;
        bitcoin.read_input(v[1]);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return (1);
    }
}