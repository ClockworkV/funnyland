#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <random>
#include <iostream>

std::default_random_engine& global_urng();
void randomize(unsigned int i = 0 );
int pick_a_number(int from, int thru);
double pick_a_number(double from, double upto);

enum class Dir{N = 'N', E = 'E', S = 'S', W = 'W', InvalidDir = '~'};
Dir intToDir(int i);

class Address: public std::pair<int, int>
{
    public:
        Address(int i = -1, int j = -1):std::pair<int, int>({i,j}){};
        Address to(Dir) const;
        std::ostream& print(std::ostream& os = std::cout);
    private:

};

const Address invalidAddress = Address({-1, -1});

#endif // UTIL_H
