#include "Card.h"

Card::Card(std::string actual_word, std::vector<std::string> restricted): word(actual_word), restricted_words(restricted){}
Card::Card(){}

void Card::setWord(std::string current_word) {
    word = current_word;
}

void Card::setRestrictedWords(std::vector<std::string> current_restricted) {
    restricted_words = current_restricted;
}

std::string Card::getWord() {
    return word;
}

std::vector<std::string> Card::getRestrictedWords() {
    return restricted_words;
}
