#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "Card.h"
#include "Player.h"

extern vector<Card> cards;
extern int current_card;
extern vector<Player> players;
extern int current_player;

class ofApp : public ofBaseApp {
    string description;
    
	public:
		void setup();
		void update();

        // Helper Methods
        vector<Card> createCards(string file_path);
        void createNewRound();
        string createCardString();
        void incrementPlayer();
        void sendToGuessers(string message);
        void checkDescription(string str);
        void checkGuesses();
        void sendPlayerRanks();
		
    ofxTCPServer TCP;
};
