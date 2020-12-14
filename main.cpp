#include "grammar.h"

#include <list>

#define INPUT_LEN 100

std::string RequestUserInput(std::string s)
{
	std::cout << s << std::endl;
	char c[INPUT_LEN];
	fgets(c, INPUT_LEN, stdin);
	if ((strlen(c) > 0) && (c[strlen(c) - 1] == '\n'))
		c[strlen(c) - 1] = '\0';
	std::cout << std::endl;
	return { c };
}

using namespace Automata;

int main(int argc, char* argv[])
{
	std::map<std::string, Grammar> grammars{};
	grammars["BasicLang"] = { "S",
	{
		{"S", "SSaAaba"},
		{"A", "bAc"},
		{"A", "d"}
	} };
	grammars["BasicLang"].SetName("BasicLang");
	
	grammars["LogicalLang"] = { "E",
	{
		{"E", "E or E"},
		{"E", "E and E"},
		{"E", "(E)"},
		{"E", "not E"},
		{"E", "true"},
		{"E", "false"}
	} };
	grammars["LogicalLang"].SetName("LogicalLang");
	
	grammars["Poetry"] = { "S",
	{
		{"S", "NP  VP ENDP"},
		{"NP", "DET  ADL  NOUN"},
		{"VP", "VERB"},
		{"VP", "VERB  ADV"},
		{"VP", "VP CONJ  VP"},
		{"ADL", "ADJ"},
		{"ADL", "ADL ADJ"},
		{"NOUN", "butterflies"},
		{"NOUN", "flowers"},
		{"NOUN", "days"},
		{"NOUN", "moons"},
		{"NOUN", "waves"},
		{"NOUN", "kisses"},
		{"NOUN", "sighs"},
		{"NOUN", "ideas"},
		{"NOUN", "winds"},
		{"ADJ", "painful"},
		{"ADJ", "yellow"},
		{"ADJ", "lonely"},
		{"ADJ", "beautiful"},
		{"ADJ", "colorless"},
		{"DET", "The"},
		{"DET", "Some"},
		{"DET", "Many"},
		{"DET", "These"},
		{"DET", "Those"},
		{"DET", "My"},
		{"VERB", "die"},
		{"VERB", "wither"},
		{"VERB", "sleep"},
		{"VERB", "wilt"},
		{"VERB", "disappear"},
		{"VERB", "decay"},
		{"ADV", "woefully"},
		{"ADV", "furiously"},
		{"ADV", "pointlessly"},
		{"ADV", "slowly"},
		{"ADV", "selflessly"},
		{"ADV", "graciously"},
		{"CONJ", "and"},
		{"CONJ", "but"},
		{"CONJ", "or"},
		{"ENDP", "."},
		{"ENDP", "!"},
		{"ENDP", "..."},
		{"ENDP", " :("}
	} };
	grammars["Poetry"].SetName("Poetry");
	
	//while (true)
	//{
	//	std::string s = RequestUserInput("=== Enter a Language name to debug it ===\n [ BasicLang, LogicalLang, Poetry ] ");
	//	s = "LogicalLang";
	//	Grammar g = grammars[s];
	//	if (g.IsValid())
	//	{
	//		std::string word = g.GenRandomWord(1607230971);
	//		std::cout << "in language \"" << s << "\", the word \"" << word << "\" Exists" << std::endl;
	//		if (g.IsInLanguage(word) == 0)
	//		{
	//			std::cout << "Debug test worked" << std::endl;
	//		}
	//		else
	//		{
	//			std::cout << "Debug test did not work" << std::endl;
	//		}
	//	}
	//}

	for (const auto g : grammars)
	{
		std::cout << g.second << std::endl;
	}
	return 0;
}