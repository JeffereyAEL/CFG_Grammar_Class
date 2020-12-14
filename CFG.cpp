#include "CFG.h"

using namespace std;
using namespace Automata;

CFG::CFG(const std::multimap<std::string, std::string>& _Cfg)
{
    D = multimap<string, Product>{};
    for (const auto pair : _Cfg)
    {
        D.insert({ pair.first, { pair.second, {""}} } );
    }
}

void CFG::operator=(const multimap<string, string>& _Cfg)
{
    D = multimap<string, Product>{};
    for (const auto pair : _Cfg)
    {
        D.insert({ pair.first, { pair.second, {""}} } );
    }
}

void CFG::operator=(const CFG& _Cfg)
{
    D = multimap<string, Product>{};
    for (const auto p : _Cfg.D)
    {
        D.insert(p);
    }
}

ProductionMap::iterator CFG::insert(const Production& _Production)
{
    return D.insert(_Production);
}

ProductionMap::iterator CFG::find(const std::string& _Variable)
{
    return D.find(_Variable);
}

std::ostream& operator<<(std::ostream& os, const CFG& cfg)
{
    for (const auto it : cfg.D)
    {
        os << it.V() << " -> \"" << it.P() << "|" << it.VP() << "|\"" << endl; 
    }
    return os;
}
