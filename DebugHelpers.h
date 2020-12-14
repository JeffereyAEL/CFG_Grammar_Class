#pragma once

#include <iostream>
#include <list>
#include <set>


template<typename Type, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::list<Type, Alloc>& l)
{
    os << "{ ";
    auto it = l.begin();
    auto end = l.size() - 1;
    for (auto i = 0; i < end; ++i, ++it)
        os << *it << ", ";
    return os << *it << " }";
}
template<typename Type, typename Comp, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::set<Type, Comp, Alloc>& s)
{
    os << "{ ";
    auto it = s.begin();
    auto end = s.size() - 1;
    for (unsigned long long i = 0; i < end; ++i, ++it)
        os << *it << ", ";
    return os << *it << " }";
}