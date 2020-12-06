#pragma once

#include <stdlib.h>
#include <string>
#include <array>
#include <map>
#include <iostream>

//class Production
// ==============================
// ===== DEFINES_/_TYPEDEFS =====
// ==============================
typedef std::pair<std::string, std::array<std::string, 2>> Production;
typedef std::array<std::string, 2> Product;

#define _variable() first
#define _product() second[0]
#define _varPrime() second[1]
