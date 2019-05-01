#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    // Sets up textfield and background
    gui.setup();
    gui.add(textField.setup("", ""));
    textField.setShape(500, 100, 400, 75);
    ofSetBackgroundColor(ofColor::dimGrey);
    
    // Network settings setup
    ofxTCPSettings settings("127.0.0.1", 647563);
    tcpClient.setup(settings);
    tcpClient.setMessageDelimiter("\n");
    
    // Setup variables
    timer_length = 60000;
    word_length = 5;
    restricted_length = 11;
    score = "0";
    current_state = "SETUP";
    describer_move = "START GAME";
    started_round = false;
    
    // Load fonts
    wordFont.load("Roboto-Light.ttf", 20);
    restrictedFont.load("Roboto-Light.ttf", 15);
    timerFont.load("NewsCycle-Regular.ttf", 20);
    displayFont.load("Boogaloo-Regular.ttf", 30);
    displayFontSmall.load("Boogaloo-Regular.ttf", 15);
    
    // Setup Sounds
    errorSound.load("142608__autistic-lucario__error.wav");
    timesUpSound.load("244932__kwahmah-02__short-buzzer.wav");
    correctAnswerSound.load("264981__renatalmar__sfx-magic.wav");
}

//--------------------------------------------------------------
void ofApp::update() {
    string action = tcpClient.receive();
    std::cout << action;
    wordFont.drawString(action, 200,200);
    /**
     * Parses through the string sent by client, certain key words will only be sent to either describer or guesser
     * STATE, SCORE and INVALID MOVE sent to all players
     * WORD sent to describer
     * STARTED ROUND and CORRECT ANSWER sent to guesser
     **/
    if (action.substr(0,6).compare("STATE:") == 0) {
        current_state = action.substr(6);
    } else if (action.substr(0,6).compare("SCORE:") == 0) {
        score = action.substr(6);
    } else if (action.substr(0,5).compare("WORD:") == 0) {
        parseCard(action);
    } else if (action.substr(0,12).compare("INVALID MOVE") == 0) {
        errorSound.play();
        textField.input = "";
        parseCard(action.substr(12));
    } else if (action.compare("STARTED ROUND") == 0) {
        started_round = true;
        ofResetElapsedTimeCounter();
    } else if (action.substr(0,14).compare("CORRECT ANSWER") == 0) {
        correctAnswerSound.play();
        if (current_state == "DESCRIBE") {
            parseCard(action.substr(14));
        }
    } else if (action.substr(0,6) == "ACTION") {
        describer_move = action.substr(6);
        clues.clear();
    } else {
        if (last_description != action && action != "") {
            last_description = action;
            clues.push_back(action);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    if (current_state.compare("SETUP") == 0) {
    // Display before the game starts
    displayFont.drawString("Press space to start the game", 200, 384);
    }
    // Create and display timer for both guesser and describer
    int timer = (timer_length - ofGetElapsedTimeMillis())/ 1000;
    if (started_round) {
        wordFont.drawString("Time Remaining: " + to_string(timer),100,75);
        
        // Ends the round when time is up
        if (timer == 0) {
            timesUpSound.play();
            tcpClient.send("END ROUND");
            started_round = false;
        }
    }
    
    // Creates screen for describer
    if (current_state.compare("DESCRIBE") == 0) {
        // Shows score and says to press 's' to start the game
        if (!started_round) {
            ofSetColor(ofColor::darkSlateBlue);
            displayFont.drawString("You have " + score + " points", 390, 330);
            displayFont.drawString("You are describing, press 's' to start the round", 200, 384);
        } else {
            // Draw the textfield
            gui.draw();
            
            // Creates the Actual Taboo Card
            ofSetColor(ofColor::purple);
            ofDrawRectangle(75, 100, 325, 100);
            ofSetColor(ofColor::whiteSmoke);
            ofDrawRectangle(75, 200, 325, 330);
            showCard();
            
            // Shows directions
            ofSetColor(ofColor::darkSlateBlue);
            displayFont.drawString("Type your clue in the text field", 500, 250);
            displayFont.drawString("Press enter to send a clue", 500, 300);
            displayFont.drawString("Press space to skip card", 500, 350);
        
            // Sends what user is typing to client
            description = toUpper(textField.getParameter().toString());
            tcpClient.send(description);
        }
    }
    
    // Creates screen for guesser
    if (current_state.compare("GUESS") == 0) {
        // Shows score and indicated player has to wait for describer to start the round
        if (!started_round) {
            ofSetColor(ofColor::darkSlateBlue);
            displayFont.drawString("You have " + score + " points", 390, 330);
            displayFont.drawString("You are guessing, the round will start once the describer chooses to start the game", 20, 384);
        } else {
            // Draw textField
            gui.draw();
            // Display Instructions
            displayFontSmall.drawString("Enter your guess in the textfield, press enter to send", 500, 150);
            displayFont.drawString("Last Move: " + describer_move, 500, 600);
            // Displays description sent from client
            displayFont.drawString("Description: ", 100, 150);
            for (int i = 0; i < clues.size(); i++) {
                displayFont.drawString(clues[i], 100, 200 + 50*i);
            }
            // Sends guesses to client
            guess = toUpper(textField.getParameter().toString());
            tcpClient.send(guess);
        }
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
    if (current_state.compare("SETUP") == 0) {
        if (key == ' ') {
            tcpClient.send("START GAME");
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

/**
 Used to change description and guess to upper case so the client can compare to the actual values which are already uppercase
 **/
string ofApp::toUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        str [i] = toupper(str[i]);
    }
    return str;
}





