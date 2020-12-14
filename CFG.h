#pragma once

#include "Production.h"

#include <map>
#include <string>

namespace Automata
{
    class CFG
    {
    private:
        std::multimap<std::string, Product> D;
    
    public:
        /// Default Empty Constructor
        CFG() : D{} {};

        /// Copy Constructor
        explicit CFG(const std::multimap<std::string, Product>& _Cfg) : D{_Cfg} {}

        /// Copy Constructor
        CFG(const CFG& _Cfg) : D{_Cfg.D} {};

        CFG(const std::multimap<std::string, std::string>& _Cfg);

        /// Converts string, string multimap into Primeless CFG
        void operator=(const std::multimap<std::string, std::string>& _Cfg);

        /// Copy Constructor
        void operator=(const CFG& _Cfg);

        ProductionMap::iterator insert(const Production& _Production);

        ProductionMap::iterator find(const std::string& _Variable);

        ProductionMap::iterator end() { return D.end(); }

        ProductionMap::iterator begin() { return D.begin(); }

        friend std::ostream& operator<<(std::ostream& os, const CFG& cfg);
    };
}
