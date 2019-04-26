#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp {
    string current_state;
    string current_word;
    vector<string> restricted;
    float time_sixty;
    float time_five;
    string description;
    bool usedRestricted;
    
public:
    void setup();
    void update();
    void draw();
    
    void skipButtonPressed();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void showCard();
    void checkInput();
    void startButtonPressed();
    void takeString(string &str);
    
    ofxPanel gui;
    
    ofTrueTypeFont wordFont;
    ofTrueTypeFont restrictedFont;
    ofTrueTypeFont timerFont;
    ofxTextField textField;
    ofxButton startButton;
    //ofxTextInputField tField;
    ofSoundPlayer errorSound;
    ofxTCPClient tcpClient;
};
