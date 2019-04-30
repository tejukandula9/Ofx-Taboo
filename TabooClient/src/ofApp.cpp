#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    // Sets up windown
    gui.setup();
    gui.add(textField.setup("", ""));
    textField.setShape(500, 100, 150, 150);
    ofSetBackgroundColor(ofColor::dimGrey);
    
    // Network settings setup
    ofxTCPSettings settings("127.0.0.1", 647563);
    tcpClient.setup(settings);
    tcpClient.setMessageDelimiter("\n");
    
    // Setup variables
    time_sixty = 60000;
    time_five = 5000;
    word_length = 5;
    restricted_length = 11;
    points = "0";
    current_state = "SETUP";
    usedRestricted = false;
    started_round = false;
    
    // Load fonts
    wordFont.load("Roboto-Light.ttf", 20);
    restrictedFont.load("Roboto-Light.ttf", 15);
    timerFont.load("NewsCycle-Regular.ttf", 20);
    displayFont.load("Boogaloo-Regular.ttf", 30);
    
    // Setup Sounds
    errorSound.load("142608__autistic-lucario__error.wav");
    timesUpSound.load("244932__kwahmah-02__short-buzzer.wav");
    correctAnswerSound.load("264981__renatalmar__sfx-magic.wav");
    
    tcpClient.send("START GAME");
}

//--------------------------------------------------------------
void ofApp::update() {
    string action = tcpClient.receive();
    std::cout <<action;
    // Parses through the string sent by client
    if (action.substr(0,6).compare("STATE:") == 0) {
        current_state = action.substr(6);
    } else if (action.substr(0,5).compare("WORD:") == 0) {
        parseCard(action);
    } else if (action.substr(0,12).compare("INVALID MOVE") == 0) {
        errorSound.play();
        parseCard(action.substr(12));
    } else if (action.substr(0,6).compare("SCORE:") == 0) {
        points = action.substr(6);
    } else if (action.compare("STARTED ROUND") == 0) {
        started_round = true;
    } else if (action.compare("CORRECT ANSWER") == 0) {
        correctAnswerSound.play();
    }
    
    // Sends contents of textField to Server, server can differentiate whether it came from guesser or describer
    if (current_state == "GUESS") {
        guess = toUpper(textField.getParameter().toString());
        tcpClient.send(guess);
        description = tcpClient.receive();
    } else {
        description = toUpper(textField.getParameter().toString());
        tcpClient.send(description);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Create a timer
    int timer = (time_sixty - ofGetElapsedTimeMillis())/ 1000;
    
    if (current_state.compare("DESCRIBE") == 0) {
        if (!started_round) {
            ofSetColor(ofColor::darkSlateBlue);
            displayFont.drawString("You have " + points + " points", 390, 330);
            displayFont.drawString("You are describing, press s to start the round", 200, 384);
        } else {
            gui.draw();
        // Creates the Actual Taboo Card
        ofSetColor(ofColor::purple);
        ofDrawRectangle(75, 100, 325, 100);
        ofSetColor(ofColor::whiteSmoke);
        ofDrawRectangle(75, 200, 325, 330);
        
        // Creates the words sent from the Client
        showCard();
        
        // Send description to server
        tcpClient.send(textField.input);
            
            if (timer == 0) {
                timesUpSound.play();
                tcpClient.send("END ROUND");
                started_round = false;
            }
        }
    } else if (current_state.compare("GUESS") == 0) {
        if (!started_round) {
            ofSetColor(ofColor::darkSlateBlue);
            displayFont.drawString("You have " + points + " points", 300, 250);
            displayFont.drawString("You are guessing, the round will start once the describer chooses to start the game", 300, 384);
        } else {
            gui.draw();
            wordFont.drawString(description, 100,100);
        }
    }
    
    // Display Timer for both guesser and describer
    if (started_round) {
        wordFont.drawString("Time Remaining: " + to_string(timer),100,75);
    }
    
}

void ofApp::keyPressed(int key) {
    if (current_state.compare("DESCRIBE") == 0) {
        if (key == 's') {
            tcpClient.send("START ROUND");
            started_round = true;
            ofResetElapsedTimeCounter();
        }
        if (key == ' ') {
            textField.input = "";
            tcpClient.send("NEW CARD");
        }
    }
    if (current_state.compare("GUESS") == 0) {
        if (key == '\r') {
            tcpClient.send(textField.input);
        }
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

void ofApp::showCard() {
    wordFont.drawString(current_word, 150, 160);
    ofSetColor(ofColor::black);
    for (int i = 0; i <restricted.size(); i++) {
        restrictedFont.drawString(restricted[i], 150, 250 + (i*50));
    }
}

/**
 * Client sends Card information in the format WORD:XYZRESTRICTED:XYZRESTRICTED:XYZRESTRICTED:, where XYZ is the words on the taboo card
 * There are no spaces in between so it is easier to parse
 **/
void ofApp::parseCard(string Card) {
    restricted.clear();
    // Looks for the string RESTRICTED: throughout the Card sent by Server
    std::string look_for = "RESTRICTED:";
    
    // Sets up the current word which is between the strings "WORD:" and "RESTRICTED:"
    size_t find = Card.find(look_for);
    current_word = Card.substr(word_length,(find - word_length));
    std::cout << current_word << endl;
    
    // Finds restricted words that are in between two "RESTRICTED:" strings
    Card = Card.substr(find);
    size_t found = Card.find(look_for, 1);
    // Loops until last "RESTRICTED:" is found
    while (found != std::string::npos) {
        std::string restricted_word = Card.substr(restricted_length, found - restricted_length);
        std::cout << restricted_word << endl;
        restricted.push_back(restricted_word);
        // Restructures the string card to remove words already added to restricted vector
        Card = Card.substr(found);
        found = Card.find(look_for, 1);
    }
}

string ofApp::toUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        str [i] = toupper(str[i]);
    }
    return str;
}





