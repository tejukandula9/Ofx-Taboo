#include "ofApp.h"

vector<Card> cards;
int current_card = 0;
vector<Player> players;
int current_player = 0;

vector<Card> createCards(string file_path) {
    vector<Card> cards;
    std::ifstream fin(file_path);
    string current_word;
    // Goes through file line by line
    while (getline(fin, current_word)) {
        // Create card object and set word to the first word
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
            TCP.send(i, "DESCRIBE");
            TCP.send(i, cards[current_card].getWord());
            for (int j = 0; j < cards[current_card].getRestrictedWords().size(); j++) {
                TCP.send(i, cards[current_card].getRestrictedWords()[j]);
            }
            TCP.send(i,"END");
            
        } else {
            TCP.send(i, "GUESS");
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    // Set up network
    ofxTCPSettings settings(647563);
    TCP.setup(settings);
    TCP.setMessageDelimiter("\n");
    
    //Create cards
    cards = createCards("/Users/tejukandula/Desktop/of_v0.10.1_osx_release/apps/myApps/TabooServer/TabooCards.txt");
}

//--------------------------------------------------------------
void ofApp::update() {

    // Create vector of players from connected clients
    for (int i = 0; i <TCP.getLastID(); i++) {
        if (!TCP.isClientConnected(i)) {
            continue;
        }
        Player p;
        p.setId(TCP.receive(i));
        p.setClientId(i);
        players.push_back(p);
    }
    
    // Create new round at start of game and at the end of each round
    //if (TCP.receive(current_player) == "NEW ROUND") {
        createNewRound();
    //}
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
