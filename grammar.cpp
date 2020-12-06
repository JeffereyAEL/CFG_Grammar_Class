#include "grammar.h"

#include <set>
#include <list>
#include <time.h>

using namespace std;

Grammar::Grammar(const string init_production, const multimap<string, string> productions) : Grammar()
{
	if (productions.find(init_production) == productions.end())
	{
		cout << "Attempt to create invalid CFG : '" << init_production << "' not found in list of products" << endl;
	}
	else
	{
		bIsValid = true;
		InitVariable = string{ init_production };
		RemoveLeftRecursion(productions);
	}
}

void Grammar::ParseProduction(Production pro)
{
	cout << pro._variable() << " -> " << pro._product() << "(" << pro._varPrime() << ")" << endl;

	Production new_pro{ "", { "", "" } };
	string variable;
	for (int pro_i = 0; pro_i < pro._product().length(); ++pro_i)
	{
		if (IsVariable(pro._product(), pro_i, variable))
		{
			pro_i += variable.length();
			new_pro = FindValidProduct(variable);
			ParseProduction(new_pro);
		}
		Match(pro._product()[pro_i]);
	}

	/// Handles Prime Variables
	if (Index < CurrStr.length())
	{
		new_pro = FindValidProduct(pro._varPrime());
		if (new_pro._variable() != "")
		{
			ParseProduction(new_pro);
		}
	}
	else
	{
		cout << "Non-prime w production " << pro._variable() << " -> " << pro._product() << "(" << pro._varPrime() << ") @ index " << Index << endl;
	}
}

bool Grammar::IsVariable(string str, int str_i, string& var)
{
	for (string v : Vars)
	{
		int i_ = str_i;
		bool match = true;
		for (const char c : v)
		{
			if (i_ < str.length())
			{
				if (str[i_++] != c)
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
			var = v;
			return true;
		}
	}
	return false;
}

Production Grammar::FindValidProduct(string var)
{
	auto it = Productions.find(var);
	bool valid = false;
	for (; it != Productions.end(); ++it)
	{
		Production p = *it;
		if ( p._variable() == var)
		{
			string pro = p._product();
			int pro_len = pro.length();
			int i = -1;
			string temp{ };
			while (!IsVariable(pro, i+1, temp))
			{
				++i;
				if (i+1 == pro_len)
					break;
			}

			//cout << "from var " << var << " subtring '" << pro.substr(0, i+1) << "'" << endl;
			//cout << "i = " << i << endl;
			cout << CurrStr.substr(Index,i + 1) << " == " << pro.substr(0, i+1)
				<< endl;
			if (CurrStr.substr(Index,i + 1) == pro.substr(0, i+1)) // Is this the correct production for this variable
			{
				//cout << CurrStr.substr(Index, i) << " == " << pro.substr(0, i) << endl;
				return *it;
				valid = true;
			}
		}
	}
	if (!valid && Index < CurrStr.length())
	{
		cout << "No valid Production found for '" << CurrStr << "' at index " << Index << " with Var '" << var << "'" << endl;
	}
	return { "", { "", "" } };
}

void Grammar::Match(const char c)
{
	//cout << "Matching" << endl;
	if (CurrStr[Index] == c || ((int)CurrStr[Index] == 32 && (int)c == 0))
	{
		++Index;
	}
	else
	{
		//cout << "Error         : Unexpected terminant in '" << CurrStr << "' where '" << c << "' was expected at index " << Index << endl;
		cout << "ERROR - char comp : '" << CurrStr[Index] << "' != '" << c << "'" << endl;
		//cout << "integer comp  : '" << (int)CurrStr[Index] << "' != '" << (int)c << "'" << endl;
		//cout << "==========" << endl;
		++Error;
	}
}

void Grammar::RemoveLeftRecursion(const multimap<string, string> productions)
{
	/// Record all the current variables this CFG wants to use
	

	for (auto it = productions.begin(); it != productions.end(); ++it)
	{
		if (Vars.find(it->first) == Vars.end())
		{
			Vars.insert(it->first);
		}
	}

	Productions = multimap<string, Product>{};

	list<string> lr;
	list<string> nonlr;
	/// For every variable we've recored, and
	for (const string v : Vars)
	{
		lr = list<string>{};
		nonlr = list<string>{};
		/// For every product associated with that variable, sort them as LR or not
		for (auto it = productions.find(v); it != productions.end(); ++it)
		{
			if (it->first == v)
			{
				string p;
				if (v == it->second.substr(0, v.length())) // Left recursion
				{
					int start = v.length();
					p = it->second.substr(start, it->second.length() - v.length());
					lr.push_back(p);
				}
				else
				{
					p = it->second;
					nonlr.push_back(p);
				}
			}
		}

		if (lr.size() > 0) // if left recursion present
		{
			string vp = v + "Prime";
			if (Vars.find(v) != Vars.end())
				cout << "Prime variable for the removal of LR, '" << vp << "' already exists in this Grammar :: this is undefined behavior and could cause errors" << std::endl;
			for (string p : nonlr)
			{
				Productions.insert({ v, { p, vp } });
				cout << v << " -> " << p << endl;
				cout << v << " -> " << p << vp << endl;

			}
			for (string p : lr)
			{
				Productions.insert({ vp, { p, vp } });
				cout << vp << " -> " << p << endl;
				cout << vp << " -> " << p << vp << endl;
			}
		}
		else
		{
			for (string p : nonlr)
			{
				Productions.insert({ v, { p, "" }});
				cout << v << " -> " << p << "" << endl;
			}
		}
	}
}

void Grammar::FetchRandomProduction(string& word, const string v)
{

	list<Product> products{};
	auto it = Productions.find(v);
	for (; it != Productions.end(); ++it)
	{
		if (it->_variable() == v)
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
	if ( p[1] != string{})
	{
		if (rand() % 2)
		{
			using_prime = true;
		}
	}
	
	//if (using_prime)
	//	cout << "from " << v << " chose : " << p[0] << p[1] << endl;
	//else
	//	cout << "from " << v << " chose : " << p[0] << endl;

	string product = p[0];
	string var{};
	for (int i = 0; i < product.length(); ++i)
	{
		if (IsVariable(product, i, var))
		{
			FetchRandomProduction(word, var);
			i += var.length()-1;
		}
		else
		{
			word += product[i];
			//cout << "currWord = " << word << endl;
		}
	}
	if (using_prime)
		FetchRandomProduction(word, p[1]);
}

int Grammar::IsInLanguage(const string s)
{
	if (bIsValid)
	{
		Index = 0;
		Error = 0;
		CurrStr = s;
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

string Grammar::GenRandomWord(const uint64_t seed)
{
	if (bIsValid)
	{
		if (!seed)
		{
			uint64_t s = time(NULL);
			srand(s);
			cout << "Random seed = " << to_string(s) << endl;
		}
		else
		{
			srand(seed);
		}
		string word{};
		FetchRandomProduction(word, InitVariable);
		return word;
	}

	cout << "Cannot use GenRandomWord with invalid CFG" << endl;
	return string{};
}