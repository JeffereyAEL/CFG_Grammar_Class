#include "grammar.h"

#include <set>
#include <list>
#include <time.h>
#include "DebugHelpers.h"

using namespace std;
using namespace Automata;

Grammar::Grammar(const string _Init_production, const multimap<string, string> _Productions) : Grammar()
{
	if (_Productions.find(_Init_production) == _Productions.end())
	{
		cout << "Attempt to create invalid CFG : '" << _Init_production << "' not found in list of products" << endl;
	}
	else
	{
		bIsValid = true;
		InitVariable = _Init_production;
		Productions = _Productions;
		for (auto it = Productions.begin(); it != Productions.end(); ++it)
			Vars.insert(it->first); // Vars is a set, so this may be redundant but we won't get duplicates
		
		RemoveLeftRecursion();
	}
}

void Grammar::ParseProduction(Production _Pro)
{
	cout << _Pro.V() << " -> " << _Pro.P() << "(" << _Pro.VP() << ")" << endl;

	Production new_pro{ "", { "", {""} } };
	string variable;
	for (int pro_i = 0; pro_i < _Pro.P().length(); ++pro_i)
	{
		if (IsVariable(_Pro.P(), pro_i, variable))
		{
			pro_i += variable.length();
			new_pro = FindValidProduct(variable);
			ParseProduction(new_pro);
		}
		Match(_Pro.P()[pro_i]);
	}

	/// Handles Prime Variables
	if (Index < CurrStr.length())
	{
		new_pro = FindValidProduct(_Pro.VP().str());
		if (new_pro.V() != "")
		{
			ParseProduction(new_pro);
		}
		else
		{
			//cout << "Production w/o Prime " << _Pro.V() << " -> " << _Pro.P() << "(" << _Pro.VP() << ") @ index " << Index << endl;
		}
	}
	else
	{
		//cout << "Production w/o Prime " << _Pro.V() << " -> " << _Pro.P() << "(" << _Pro.VP() << ") @ index " << Index << endl;
	}

	cout << "Leaving ParseProduction" << endl;
}

bool Grammar::IsVariable(string _Str, int _Str_i, string& _Var)
{
	for (string v : Vars)
	{
		int i_ = _Str_i;
		bool match = true;
		for (const char c : v)
		{
			if (i_ < _Str.length())
			{
				if (_Str[i_++] != c)
				{
					match = false;
					break;
				}
			}
			else
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			_Var = v;
			cout << "Leaving IsVariable A" << endl;
			return true;
		}
	}
	cout << "Leaving IsVariable B" << endl;
	return false;
}

Production Grammar::FindValidProduct(const string _Var)
{
	auto it = Productions.find(_Var);
	for (; it != Productions.end(); ++it)
	{
		Production p = *it;
		if ( p.V() == _Var)
		{
			string pro = p.P();
			const int pro_len = pro.length();
			int i = -1;
			string temp{ };
			while (!IsVariable(pro, i+1, temp))
			{
				++i;
				if (i+1 == pro_len)
					break;
			}
			
			if (CurrStr.substr(Index,i + 1) == pro.substr(0, i+1))
			{
				//cout << CurrStr.substr(Index,i + 1) << " == " << pro.substr(0, i+1) << endl;
				cout << "Leaving FindValidProduct A" << endl;
				return *it;
			}
		}
	}
	//cout << "No valid Production found for '" << CurrStr << "' at index " << Index << " with Var '" << _Var << "'" << endl;
	cout << "Leaving FindValidProduct B" << endl;
	return { "", { "", {""} } };
}

void Grammar::Match(const char c)
{
	if (CurrStr[Index] == c || (static_cast<int>(CurrStr[Index]) == 32 && static_cast<int>(c) == 0))
	{
		++Index;
	}
	else
	{
		//cout << "ERROR - char comp : '" << CurrStr[Index] << "' != '" << c << "'" << endl;
		++Error;
	}
	cout << "Leaving Match" << endl;
}

void Grammar::RemoveLeftRecursion()
{
	list<Product> lr, nonlr;
	string p;
	int start, end;
	CFG temp_productions{};
	bool dirty = true;
	
	while (dirty)
	{
		dirty = false;

		temp_productions = Productions; // Set up temp to be read from
		Productions = CFG{};  			// clear the class Productions to be refilled
		
		for (const string v : Vars)
		{
			lr = list<Product>{};
			nonlr = list<Product>{};
			/// For every product associated with that variable, sort them as LR or not
			for (auto it = temp_productions.find(v); it != temp_productions.end(); ++it)
			{
				if (it->V() == v)
				{
					if (v == it->P().substr(0, v.length())) // Left recursion
						lr.push_back( it->PRODUCT() );
					else
						nonlr.push_back(it->PRODUCT());
				}
			}
			
			if (lr.size() == 0)  		// No LR exists for this Variable
			{
				for (Product pro : nonlr)
					Productions.insert({ v, pro });
			}
			else						// LR Exists for this Variable
			{
				dirty = true;
				
				Variable vp = nonlr.begin()->second;
				vp += (v + "Prime");
				for (Product pro : nonlr)
				{
					Productions.insert({ v, { pro.first, vp } });
				}
				for (Product pro : lr)
				{
					
					start = v.length();
					end = pro.first.length() - v.length();
					p = pro.first.substr(start, end);
					Productions.insert({ vp.str(), { p, vp } });
				}
			}
		
		}
	}
}

void Grammar::FetchRandomProduction(string& _Word, const string _V)
{
	list<Product> products{};
	auto it = Productions.find(_V);
	for (; it != Productions.end(); ++it)
	{
		if (it->V() == _V)
		{
			products.push_back(it->second);
		}
	}

	unsigned index = rand() % products.size();
	auto it2 = products.begin();
	for (unsigned i = 0; i < index; ++i)
		++it2;
	Product p = *it2;
	bool using_prime = false;
	if ( p.second.str() != string{})
	{
		if (rand() % 2)
		{
			using_prime = true;
		}
	}
	string product = p.first;
	string var{};
	for (int i = 0; i < product.length(); ++i)
	{
		if (IsVariable(product, i, var))
		{
			FetchRandomProduction(_Word, var);
			i += var.length()-1;
		}
		else
		{
			_Word += product[i];
			//cout << "currWord = " << word << endl;
		}
	}
	if (using_prime)
		FetchRandomProduction(_Word, p[1]);
}

int Grammar::IsInLanguage(const string _S)
{
	if (bIsValid)
	{
		Index = 0;
		Error = 0;
		CurrStr = _S;
		Production pro = FindValidProduct(InitVariable);
		ParseProduction(pro);
		if (Index < CurrStr.length() && !Error)
		{
			cout << "Parser exiting without evaluating full length of string" << endl;
			--Error;
		}
		return Error;
	}

	cout << "Cannot Identify IsInLanguage with invalid CFG" << endl;
	return false;
}

string Grammar::GenRandomWord(const uint64_t _Seed)
{
	if (bIsValid)
	{
		if (!_Seed)
		{
			uint64_t s = time(NULL);
			srand(s);
			cout << "Random seed = " << to_string(s) << endl;
		}
		else
		{
			srand(_Seed);
		}
		string word{};
		FetchRandomProduction(word, InitVariable);
		return word;
	}

	cout << "Cannot use GenRandomWord with invalid CFG" << endl;
	return string{};
}

std::ostream& operator<<(std::ostream& os, const Grammar& g)
{
	return os << g.Name << endl << g.Productions;
}
