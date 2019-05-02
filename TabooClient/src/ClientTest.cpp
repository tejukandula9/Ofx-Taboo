#define CATCH_CONFIG_MAIN
#include "/Users/tejukandula/Documents/STLIntro/catch.hpp"
#include "CardParser.h"

TEST_CASE("Medium length word") {
    std::string card = "WORD:MILKRESTRICTED:DRINKRESTRICTED:COWRESTRICTED:CEREALRESTRICTED:";
    parseCard(card);
    SECTION("Check word") {
        REQUIRE(current_word == "MILK");
    }
    SECTION("Check correct number of restricted words") {
        REQUIRE(restricted.size() == 3);
    }
    SECTION("Check restricted words") {
        std::vector<std::string> test_restricted{"DRINK","COW","CEREAL"};
        REQUIRE(restricted == test_restricted);
    }
}

TEST_CASE("Current word is two words") {
    std::string card = "WORD:HARRY POTTERRESTRICTED:WIZARDRESTRICTED:HERMIONERESTRICTED:RONRESTRICTED:VOLDEMORTRESTRICTED:JK ROWLINGRESTRICTED:";
    parseCard(card);
    SECTION("Check word") {
        REQUIRE(current_word == "HARRY POTTER");
    }
    SECTION("Check correct number of restricted words") {
        REQUIRE(restricted.size() == 5);
    }
    SECTION("Check restricted words") {
        std::vector<std::string> test_restricted{"WIZARD","HERMIONE","RON","VOLDEMORT", "JK ROWLING"};
        REQUIRE(restricted == test_restricted);
    }
}

TEST_CASE("Only one restricted word") {
    std::string card = "WORD:CEREALRESTRICTED:FROOT LOOPSRESTRICTED:";
    parseCard(card);
    SECTION("Check word") {
        REQUIRE(current_word == "CEREAL");
    }
    SECTION("Check correct number of restricted words") {
        REQUIRE(restricted.size() == 1);
    }
    SECTION("Check restricted words") {
        std::vector<std::string> test_restricted{"FROOT LOOPS"};
        REQUIRE(restricted == test_restricted);
    }
}


