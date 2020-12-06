#pragma once

#include "Production.h"

#include <string>
#include <map>
#include <set>

class Grammar
{
	// ======================
	// ===== ATTRIBUTES =====
	// ======================
private:
	/// A LR friendly format for storing CFGs
	std::multimap<std::string, Product> Productions;

	std::set<std::string> Vars;

	/// The Starting Production
	std::string InitVariable;

	/// The current string being compared with IsInLanguage()
	std::string CurrStr;

	/// Whether this is a valid Grammar
	bool IsValid;

	/// The current location in CurrString
	int Index;

	/// The number of errors we've encounted while parsing
	/// > 0 means invalid, == 0 means within language, < 0 means incomplete parse
	int Error;

protected:
public:
	// ======================================
	// ===== CONSTRUCTORS_/_DESTRUCTORS =====
	// ======================================
private:
protected:
public:
	/// Generates a Grammar
	Grammar() : IsValid{ false }, Productions{}, Vars{}, InitVariable{}, CurrStr{}, Index{0}, Error{0} {};
	Grammar(const std::string init_production, const std::multimap<std::string, std::string> productions);

	// ===================
	// ===== METHODS =====
	// ===================
private:
	/// Iterates through a production and compares terminants or calls variables when needed
	void ParseProduction(Production pro);

	/// Checks to see if the place in our string is a Variable within this language.
	/// Returns true if it is and stores the result of FindValidProduction in the reference variable 'pro'
	bool IsVariable(std::string str, int str_i, std::string& var);

	/// Finds a valid production for a given variable to use with our string
	/// if found returns the appropriate production, otherwise throws an error and increments the error counter
	Production FindValidProduct(std::string var);

	/// Compares the character we're currently at in the string
	/// Increments the Index if they're the same, otherwise throws an error and increments the error counter
	void Match(const char c);

	void RemoveLeftRecursion(const std::multimap<std::string, std::string> productions);

	void FetchRandomProduction(std::string& word, const std::string v);

protected:
public:
	/// Returns whether the given string can be produced with this CFG
	int IsInLanguage(const std::string s);

	/// Returns a random "Word" from within the language
	std::string GenRandomWord(const uint64_t seed = 0); /*** TODO: Add in a seed that dicates the random generation */
};