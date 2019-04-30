#include "ofApp.h"

std::vector<Card> cards;
int current_card = 0;
std::vector<Player> players;
int current_player = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    // Set up network
    ofxTCPSettings settings(647563);
    TCP.setup(settings);
    TCP.setMessageDelimiter("\n");
    
    //Create and shuffle cards
    cards = createCards("/Users/tejukandula/Documents/TabooServer/TabooCards.txt");
    std::random_shuffle(cards.begin(), cards.end());
}
//--------------------------------------------------------------
void ofApp::update() {
    // Adds players to players vector once connected
    for (int i = 0; i <TCP.getLastID(); i++) {
        // Checks if player is already connected and added to player vector
        bool alreadyPlaying = false;
        for (int j = 0; j < players.size(); j++) {
            if (players[j].getClientId() == i) {
                alreadyPlaying = true;
            }
        }
        if (!TCP.isClientConnected(i) || alreadyPlaying) {
            continue;
        }
        Player p;
        p.setClientId(i);
        players.push_back(p);
    }
    
    // Parses through strings sent by current describer
    string action = TCP.receive(current_player);
    if (action.compare("START GAME") == 0) {
        createNewRound();
    } else if (action.compare("START ROUND") == 0){
        TCP.send(current_player, createCardString());
        sendToGuessers("STARTED ROUND");
    } else if (action.compare("NEW CARD") == 0) {
        current_card++;
        TCP.send(current_player, createCardString());
    } else if (action.compare("END ROUND") == 0) {
        // Sends the current score to all the players at the end of a round
        for (int i = 0; i < players.size(); i ++) {
            TCP.send(i, "SCORE:" + to_string(players[i].getScore()));
        }
        incrementPlayer();
        createNewRound();
    } else {
        description = action;
        std::cout << description;
        checkDescription(description);
        // Sends description out to all the guessers
        sendToGuessers(description);
    }
    
    // Checks guesses from all the guessers
    for (int i = 0; i < TCP.getLastID(); i++) {
        if (i == current_player) {
            continue;
        }
        if (TCP.receive(i).compare(cards[current_card].getWord()) == 0) {
            TCP.send(i, "CORRECT ANSWER");
            players[i].addPoints(2);
            players[current_player].addPoints(1);
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

vector<Card> ofApp::createCards(string file_path) {
    vector<Card> cards;
    std::ifstream fin(file_path);
    string current_word;
    
    // Goes through file line by line
    while (getline(fin, current_word)) {
        // Create card object and set word to the first  word
        Card c;
        c.setWord(current_word);
        vector<string> restricted;
        // Create vector of restricted words until reaching an empty line
        while (current_word != "") {
            getline(fin,current_word);
            restricted.push_back(current_word);
        }
        // Remove last vector because it is an empty line
        restricted.pop_back();
        c.setRestrictedWords(restricted);
        cards.push_back(c);
    }
    return cards;
}

void ofApp::createNewRound() {
    for (int i = 0; i < TCP.getLastID(); i++) {
        if (i == current_player) {
            TCP.send(i, "STATE:DESCRIBE");
        } else {
            TCP.send(i, "STATE:GUESS");
        }
    }
}

string ofApp::createCardString() {
    string card = "WORD:" + cards[current_card].getWord();
    
    // Adds all restricted words to the string
    for (int j = 0; j < cards[current_card].getRestrictedWords().size(); j++) {
        card += "RESTRICTED:" + cards[current_card].getRestrictedWords()[j];
    }
    
    // End string with "RESTRICTED:" so it's easier to parse
    card += "RESTRICTED:";
    return card;
}

void ofApp::checkDescription(string str) {
    // Checks whether player used the word in their description
    if (str.find(cards[current_card].getWord()) != std::string::npos) {
        current_card++;
        TCP.send(current_player, "INVALID MOVE" + createCardString());
    }
    
    // Checks whether player used a restricted word in their description
    for (int i = 0; i < cards[current_card].getRestrictedWords().size(); i++) {
        string r = cards[current_card].getRestrictedWords()[i];
        if (str.find(r) != std::string::npos) {
            current_card++;
            TCP.send(current_player, "INVALID MOVE" + createCardString());
        }
    }
}

void ofApp::incrementPlayer() {
    // Checks to see if the current player is the last player in the vector
    if (current_player == (players.size() - 1)) {
        current_player = 0;
    } else {
        current_player++;
    }
}

void ofApp::sendToGuessers(string message) {
    for (int i = 0; i < players.size(); i++) {
        if (i == current_player) {
            continue;
        }
        TCP.send(i, message);
    }
}
