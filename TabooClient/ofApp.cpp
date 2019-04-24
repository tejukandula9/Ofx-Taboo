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
    wordFont.drawString(tcpClient.receive(), 150, 160);
    ofSetColor(ofColor::black);
    /**
    while (tcpClient.receive() != "END") {
        int i = 0;
        restrictedFont.drawString(tcpClient.receive(), 150, 250 + (i*50));
        i++;
    }
     **/
}

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    
    // Network settings setup
    ofxTCPSettings settings("127.0.0.1", 647563);
    tcpClient.setup(settings);
    tcpClient.setMessageDelimiter("\n");
    tcpClient.send(createId());
    
    // Start Button setup
    gui.add(startButton.setup("START"));

    time = 60000;
    
    // Load fonts
    wordFont.load("Roboto-Light.ttf", 20);
    restrictedFont.load("Roboto-Light.ttf", 15);
    timerFont.load("NewsCycle-Regular.ttf", 20);
    
    // Setup Textbox if the state is describe
    if (tcpClient.receive() == "DESCRIBE") {
    gui.add(textField.setup("", ""));
    textField.setShape(500, 100, 150, 150);
    }
    
    //tField.setup();
    //tField.setBounds(500, 500, 30, 30);
    //tField.setMultiline(true);
    
    // Setup Soounds
    errorSound.load("142608__autistic-lucario__error.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (tcpClient.receive() == "DESCRIBE") {
    // Creates the Actual Taboo Card
    ofSetColor(ofColor::purple);
    ofDrawRectangle(75, 100, 325, 100);
    ofSetColor(ofColor::white);
    ofDrawRectangle(75, 200, 325, 330);
        
    // Creates the words sent from the Client
    //showCard();
        
    // Create a Timer
    int timer = (time - ofGetElapsedTimeMillis())/ 1000;
    wordFont.drawString("Time Remaining: " + to_string(timer),100,75);
    }
    
    //tField.draw();
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
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
}



