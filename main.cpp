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

int main(int argc, char* argv[])
{
	std::cout << " === Grammar Basic === " << std::endl;
	std::map<std::string, Grammar> grammars{};
	grammars["BasicSLang"] = { "S",
	{
		{"S", "aAaba"},
		{"A", "bAc"},
		{"A", "d"}
	} };

	std::cout << std::endl << " === Logical Grammar w/ LR === " << std::endl;
	grammars["LogicalLang"] = { "E",
	{
		{"E", "E or E"},
		{"E", "E and E"},
		{"E", "(E)"},
		{"E", "not E"},
		{"E", "true"},
		{"E", "false"}
	} };

	std::cout << std::endl << " === Crappy Poem Grammar === " << std::endl;
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
		{"ADV", "seflessly"},
		{"ADV", "graciously"},
		{"CONJ", "and"},
		{"CONJ", "but"},
		{"CONJ", "or"},
		{"ENDP", "."},
		{"ENDP", "!"},
		{"ENDP", "..."},
		{"ENDP", " :("}
	} };

	/*while (true)
	{
		
		std::string s = RequestUserInput("Input your desired string to parse: ");

		Grammar grammar = *(--grammars.end());
		int error = grammar.IsInLanguage(s);
		if (error == 0)
			std::cout << "\"" << s << "\" is in language" << std::endl << std::endl;
		else if (error > 0)
			std::cout << "\"" << s << "\" is not in language" << std::endl << std::endl;
		else
			std::cout << "\"" << s << "\" may be in language" << std::endl << std::endl;
	}*/
	while (true)
	{
		std::string s = RequestUserInput("=== Press ENTER to produce random words ===");
		//for (auto it : grammars)
		//{
		//	std::cout << "in language " << it.first << " word \"" << it.second.GenRandomWord() << " Exists" << std::endl;
		//}
		std::cout << "in language \"Poetry\", word \"" << grammars["Poetry"].GenRandomWord() << "\" Exists" << std::endl;
	}

	return 0;
}