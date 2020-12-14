#pragma once

#include "CFG.h"
#include "Production.h"

#include <string>
#include <map>
#include <set>

namespace Automata
{
	class Grammar
	{
		// ======================
		// ===== ATTRIBUTES =====
		// ======================
		private:
		std::string Name;
	
		/// A LR friendly format for storing CFGs
		CFG Productions;

		std::set<std::string> Vars;

		/// The Starting Production
		std::string InitVariable;

		/// The current string being compared with IsInLanguage()
		std::string CurrStr;

		/// Whether this is a valid Grammar
		bool bIsValid;

		/// The current location in CurrString
		int Index;

		/// The number of errors we've encountered while parsing
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
		/// Generates default empty grammar
		Grammar() : Name{}, Productions{}, Vars{}, InitVariable{}, CurrStr{}, bIsValid{ false }, Index{0}, Error{0} {};

		/// Generates grammars
		Grammar(const std::string _Init_production, const std::multimap<std::string, std::string> _Productions);

		// =============================
		// ===== GETTERS_/_SETTERS =====
		// =============================
		private:
	protected:
	public:
		bool IsValid() const { return bIsValid; }

		void SetName(const std::string& name) { Name = name; }
		// ===================
		// ===== METHODS =====
		// ===================
		private:
		/// Iterates through a production and compares terminants or calls variables when needed
		void ParseProduction(Production _Pro);

		/// Checks to see if the place in our string is a Variable within this language.
		/// Returns true if it is and stores the result of FindValidProduction in the reference variable 'pro'
		bool IsVariable(std::string _Str, int _Str_i, std::string& _Var);

		/// Finds a valid production for a given variable to use with our string
		/// if found returns the appropriate production, otherwise throws an error and increments the error counter
		Production FindValidProduct(std::string _Var);

		/// Compares the character we're currently at in the string
		/// Increments the Index if they're the same, otherwise throws an error and increments the error counter
		void Match(const char c);

		void RemoveLeftRecursion(); // TODO: Fix our multi-recursion loop ( not re-creating old Primes(?) )

		void FetchRandomProduction(std::string& _Word, const std::string _V);
	
	protected:
	public:
		/// Returns whether the given string can be produced with this CFG
		int IsInLanguage(const std::string _S);

		/// Returns a random "Word" from within the language
		std::string GenRandomWord(const uint64_t _Seed = 0);

		friend std::ostream& operator<<(std::ostream& os, const Grammar& g);
	};
}