#pragma once

#include <string>
#include <array>
#include <map>
#include <iostream>
#include <ostream>

//class Production
// ==============================
// ===== DEFINES_/_TYPEDEFS =====
// ==============================

namespace Automata
{
    class Variable
    {
    private:
        std::string Var;
        unsigned Degree;

    public:
        Variable() : Var{}, Degree{0} {};
        Variable(const std::string& var) : Var{var}, Degree{0} {};

        Variable& operator++() { Degree++; return *this; }

        std::string substr(unsigned s, unsigned e) const { return Var.substr(s,e); }

        unsigned length() const { return Var.length(); }

        std::string str() const { return Var; }

        bool operator==(const std::string& other) const { return false; }
        
        bool operator==(const Variable& other) const { return Var == other.Var && Degree == other.Degree; }

        void operator+=(const std::string& s);

        friend std::ostream& operator<<(std::ostream& os, const Variable& p);
    };

    typedef std::pair<std::string, Automata::Variable> Product;
    typedef std::pair<std::string, Product> Production;
    typedef std::multimap<std::string, Product> ProductionMap;

#define V() first
#define P() second.first
#define VP() second.second
#define PRODUCT() second
}
