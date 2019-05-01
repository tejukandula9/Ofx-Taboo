/**
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ofApp.h"

ofApp app;
TEST_CASE("Parse with medium length word") {
    string card = "WORD:MILKRESTRICTED:DRINKRESTRICTED:COWRESTRICTED:CEREAL";
    app.parseCard(card);
}
**/
