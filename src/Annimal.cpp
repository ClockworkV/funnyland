#include "Annimal.h"

using namespace std;

annimal::annimal()
:funnimal()
{
    //ctor
}

Funnimal annimal::spawn()
{
    return make_shared<annimal>();
}

void annimal::printType(std::ostream& os) const
{
    os << "A";
}
