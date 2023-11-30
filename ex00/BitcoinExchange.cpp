#include "BitcoinExchange.hpp"

btc::btc()
{
    std::ifstream   data_base("data.csv", std::ifstream::in);
    std::string     line;

    if (!data_base.is_open())
        throw   std::logic_error("Error: data.csv not exist or permission denied!");
    std::getline(data_base, line);
    while (!data_base.eof())
    {
        std::getline(data_base, line);
        if (!line.empty())
            this->DB[line.substr(0, line.find(","))] = std::atof(line.substr(line.find(",") + 1).c_str());
    }
}

btc::btc(const btc& other)
{
    *this = other;
}

btc&    btc::operator=(const btc& other)
{
    (void)other;
    return (*this);
}

btc::~btc()
{}

size_t  ft_count(std::string str, char c)
{
    size_t  count = 0;
    size_t  i;

    for (i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return (count);
}

bool    for_all(std::string str, int ft(int))
{
    for (unsigned int i = 0; str[i]; i++)
        if (!ft(str[i]))
            return (0);
    return (1);
}


void    btc::check_date(std::string date, std::string bad)
{
    std::string months_days[] = {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};
    std::string year;
    std::string month;
    std::string day;
    size_t      first;

    if (ft_count(date, '-') != 2)
        throw   (std::logic_error(bad));
    first = date.find('-');
    year = date.substr(0, first);
    if (year.length() != 4 || !for_all(year, std::isdigit))
        throw   (std::logic_error(bad.append("-> year error!")));
    if (std::atoi(date.c_str()) % 4 == 0)
        months_days[1] = "29";
    month = date.substr(first + 1, 2);
    if (month.length() != 2 || !for_all(month, std::isdigit))
        throw   (std::logic_error(bad.append("-> month error!")));
    if (month < "01" || month > "12")
        throw   (std::logic_error(bad.append("-> month error!")));
    day = date.substr(first + 4);
    if (day.length() != 2 || !for_all(day, std::isdigit))
        throw   (std::logic_error(bad.append("-> day error!")));
    if (day < "01" || day > months_days[std::atoi(month.c_str()) - 1])
        throw   (std::logic_error(bad.append("-> day error!")));
    if (year < "2009" || (year == "2009" && month == "01" && day < "02"))
        throw   (std::logic_error(date.append(" : date befor bitcoin's born!")));
}

std::string    btc::is_float(std::string str)
{
    size_t  point;
    size_t  zero;

    std::string float_characters(".0123456789");
    for (unsigned int i = 1; i < str.size(); i++)
        if (float_characters.find(str[i]) == std::string::npos)
            throw   std::logic_error("is not a float number!");
    if (ft_count(str, '.') > 1)
        throw   std::logic_error("is not a float number!");
    if (str[0] == '-')
        throw   std::logic_error("not a positive number.");
    else if (str[0] == '+')
        str = str.substr(1);
    else if (!std::isdigit(str[0]))
        throw   std::logic_error("is not a float number!");
    point = str.find('.');
    for (zero = 0; str[zero] == '0'; zero++);
    if (point == zero)
        str = str.substr(zero - 1);
    else
        str = str.substr(zero);
    if (point != std::string::npos && point - zero > 4)
        throw   std::logic_error("too large a number.");
    else if (point == std::string::npos && str.length() > 4)
        throw   std::logic_error("too large a number.");
    return (str);
}

void    btc::read_line(std::string line)
{
    std::map<std::string, float>::iterator  it;
    std::string bad = std::string("bad input => ").append(line);
    std::string date;
    std::string value;
    float       d_v;

    if (line.empty() || ft_count(line, '|') != 1)
        throw   std::logic_error(bad);
    date = line.substr(0, line.find('|') - 1);
    check_date(date, bad);
    value = line.substr(line.find('|') + 2);
    value = is_float(value);
    it = this->DB.lower_bound(date);
    if (it->first != date)
        it--;
    d_v = std::atof(value.c_str());
    if (d_v > 1000)
        throw   std::logic_error(std::string("too large a number."));
    std::cout<<date<<" => "<<d_v<<" = "<<d_v * it->second<<std::endl;
}

void    btc::read_input(std::string  infile)
{
    std::ifstream   in(infile.c_str(), std::ifstream::in);
    std::string     line;

    if (!in.is_open())
        throw   std::logic_error(std::string("Error: No such file or Permission denied : ").append(infile));
    std::getline(in, line);
    while (!in.eof())
    {
        std::getline(in, line);
        try
        {
            read_line(line);
        }
        catch(const std::exception& e)
        {
            std::cout<<"Error: "<<e.what()<<std::endl;
        }
    }
}