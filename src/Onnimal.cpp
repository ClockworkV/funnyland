#include "Onnimal.h"

using namespace std;

onnimal::onnimal()
:funnimal()
{
    //ctor
}

Funnimal onnimal::spawn()
{
    return make_shared<onnimal>();
}

void onnimal::printType(std::ostream& os) const
{
    os << "O";
}
