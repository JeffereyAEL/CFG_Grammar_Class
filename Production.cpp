#pragma once

#include "Production.h"

using namespace std;
using namespace Automata;

void Variable::operator+=(const std::string& s)
{
    if ( Var == "")
        Var = s;
    else if (Var == s)
        Degree++;
}

ostream& operator<<(ostream& os, const Variable& p)
{
    return os << p.Var << p.Degree;
}