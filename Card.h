#include <string>
#include <vector>

class Card {
    std::string word;
    std::vector<std::string> restricted_words;
    
public:
    Card();
    Card(std::string actual_word, std::vector<std::string> restricted);
    
    void setWord(std::string current_word);
    void setRestrictedWords(std::vector<std::string> current_restricted);
    std::string getWord();
    std::vector<std::string> getRestrictedWords();
};
