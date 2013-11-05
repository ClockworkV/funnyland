#include "Bnnimal.h"

using namespace std;

bnnimal::bnnimal()
:funnimal()
{
    //ctor
}

Funnimal bnnimal::spawn()
{
    return make_shared<bnnimal>();
}

void bnnimal::printType(std::ostream& os) const
{
    os << "B";
}
