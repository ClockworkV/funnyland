#include "Util.h"
#include <random>

using namespace std;

default_random_engine & global_urng()
{
    static default_random_engine u {};
    return u;
}

void randomize(unsigned int i)
{
    if (0 == i){
        static random_device rd {};
        global_urng().seed( rd() );
    } else {
        global_urng().seed( i );
    }
}

int pick_a_number(int from, int thru)
{
    static uniform_int_distribution<> d {};
    using parm_t = decltype(d)::param_type;
    return d(global_urng(), parm_t {from, thru});
}

double pick_a_number(double from, double upto)
{
    static uniform_real_distribution<> d {};
    using parm_t = decltype(d)::param_type;
    return d(global_urng(), parm_t {from, upto});
}

Dir intToDir(int i)
{
    return  i == 1? Dir::N :
            i == 2? Dir::E :
            i == 3? Dir::S :
            i == 4? Dir::W :
            Dir::InvalidDir;
}

ostream& Address::print(ostream& os)
{
    os << '(' << this->first << ',' << this->second << ')' ;
    return os;
}

Address Address::to(Dir d) const
{
    Address a(this->first, this->second);
    switch (d) {
    case Dir::N: {
        a.first -= 1;
        break;
    }
    case Dir::E: {
        a.second += 1;
        break;
    }
    case Dir::S: {
        a.first += 1;
        break;
    }
    case Dir::W: {
        a.second -= 1;
        break;
    }
    default:
        a.first = -1;
        a.second = -1;
    }
    return a;
}
