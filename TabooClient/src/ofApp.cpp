#include "ofApp.h"

std::string createId() {
    std:: string id;
    for (int i = 0; i < 8; i++) {
        int random = rand() % 10;
        id += std::to_string(random);
    }
    return id;
}

void ofApp::showCard() {
    wordFont.drawString(current_word, 150, 160);
    ofSetColor(ofColor::black);
    for (int i = 0; i <restricted.size(); i++) {
        restrictedFont.drawString(restricted[i], 150, 250 + (i*50));
    }
}

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(textField.setup("", ""));
    textField.setShape(500, 100, 150, 150);
    
    // Start Button setup
    gui.add(startButton.setup("START"));
    
    // Network settings setup
    ofxTCPSettings settings("127.0.0.1", 647563);
    tcpClient.setup(settings);
    tcpClient.setMessageDelimiter("\n");
    tcpClient.send(createId());
    
    // Setup variables
    time_sixty = 60000;
    time_five = 5000;
    current_state = "SETUP";
    usedRestricted = false;
    
    // Load fonts
    wordFont.load("Roboto-Light.ttf", 20);
    restrictedFont.load("Roboto-Light.ttf", 15);
    timerFont.load("NewsCycle-Regular.ttf", 20);
    
    //tField.setup();
    //tField.setBounds(500, 500, 30, 30);
    //tField.setMultiline(true);
    
    // Setup Sounds
    errorSound.load("142608__autistic-lucario__error.wav");
    
    //textBox.init();
    //ofAddListener(textBox.evtEnter, this, &ofApp::takeString);
}

//--------------------------------------------------------------
void ofApp::update() {
    string action = tcpClient.receive();
    std::cout <<action;
    // Checks for the board state(whether to guess or describe)
    if (action.substr(0,6).compare("STATE:") == 0) {
        current_state = action.substr(6, action.length());
    } else if (action.substr(0,5).compare("WORD:") == 0) {
        current_word = action.substr(5, action.length());
    } else if (action.substr(0,11).compare("RESTRICTED:") == 0) {
        restricted.push_back(action.substr(11, action.length()));
    }else if (action.compare("INVALID MOVE") == 0) {
        errorSound.play();
    } else {
        description = action;
    }
    
    tcpClient.send(textField.input);
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();
    if (current_state.compare("DESCRIBE") == 0) {
        // Creates the Actual Taboo Card
        ofSetColor(ofColor::purple);
        ofDrawRectangle(75, 100, 325, 100);
        ofSetColor(ofColor::white);
        ofDrawRectangle(75, 200, 325, 330);
        
        // Creates the words sent from the Client
        showCard();
        
        // Create a Timer
        int timer = (time_sixty - ofGetElapsedTimeMillis())/ 1000;
        wordFont.drawString("Time Remaining: " + to_string(timer),100,75);
        
        // Send description to server
        tcpClient.send(textField.input);
    } else if (current_state.compare("GUESS") == 0) {
        tcpClient.send(textField.input);
        wordFont.drawString(description, 100,100);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') {
        errorSound.play();
        tcpClient.send("NEW ROUND");
    }
    if (key == ' ') {
        restricted.clear();
        tcpClient.send("NEW CARD");
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

void ofApp::startButtonPressed() {
    tcpClient.send("NEW ROUND");
    wordFont.drawString("aldskjf", 500, 500);
}

void ofApp::takeString(string &str) {
}




