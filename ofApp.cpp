#include "ofApp.h"

vector<Card> cards;
int current_card = 0;

std::string toUpper(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

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

void ofApp::showCard() {
    wordFont.drawString(cards[current_card].getWord(), 150, 160);
    ofSetColor(ofColor::black);
    for (int i = 0; i <cards[current_card].getRestrictedWords().size(); i++) {
        restrictedFont.drawString(cards[current_card].getRestrictedWords()[i], 150, 250 + (i*50));
    }
}

void ofApp::checkInput() {
    std::string input = toUpper(textField.input);
    
    if (input.find(cards[current_card].getWord()) != string::npos) {
        errorSound.play();
        current_card++;
        showCard();

    } else {
        for (int i = 0; i < cards[current_card].getRestrictedWords().size(); i++) {
            if (input.find(cards[current_card].getRestrictedWords()[i])
                != string::npos) {
                errorSound.play();
                current_card++;
                showCard();
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::setup() {
    cards = createCards("/Users/tejukandula/Documents/FinalProject/TabooCards.txt");
    time = 60000;
    
    // Load fonts
    wordFont.load("Roboto-Light.ttf", 20);
    restrictedFont.load("Roboto-Light.ttf", 15);
    timerFont.load("NewsCycle-Regular.ttf", 20);
    
    // Setup Textbox
    gui.setup();
    gui.add(textField.setup("", ""));
    textField.setShape(500, 100, 150, 150);
    
    // Setup Soounds
    errorSound.load("142608__autistic-lucario__error.wav");
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Creates the Actual Taboo Card
    ofSetColor(ofColor::purple);
    ofFill();
    ofDrawRectangle(75, 100, 325, 100);
    ofSetColor(ofColor::white);
    ofDrawRectangle(75, 200, 325, 330);
    showCard();
    
    // Create a Timer
    float timer = (time - ofGetElapsedTimeMillis())/ 1000;
    //ofDrawBitmapString(timer, 200, 50);
    
    wordFont.drawString(to_string(timer),200,200);
    //timerFont.drawString(timer, 200, 50);
    
    checkInput();
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        current_card++;
        showCard();
    } else {
        checkInput();
    }
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
void ofApp::mousePressed(int x, int y, int button) {
    
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



