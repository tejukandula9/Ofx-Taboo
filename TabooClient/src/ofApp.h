#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp {
    string current_state;
    string current_word;
    vector<string> restricted;
    vector<string> clues;
    vector<string> guesses;
    string description;
    string guess;
    string score;
    string rank;
    string describer_move;
    string last_description;
    string last_guess;
    float timer_length;
    bool started_round;
    
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
    
    // Helper Methods
    void showCard();
    void parseCard(string card);
    string toUpper(string str);
    
    ofxPanel gui;
    
    // Font variables
    ofTrueTypeFont displayFont;
    ofTrueTypeFont displayFontSmall;
    ofTrueTypeFont wordFont;
    ofTrueTypeFont restrictedFont;
    ofTrueTypeFont timerFont;
    
    // TextField
    ofxTextField textField;
    
    // Sound variables
    ofSoundPlayer errorSound;
    ofSoundPlayer timesUpSound;
    ofSoundPlayer correctAnswerSound;
    
    // Network Variable
    ofxTCPClient tcpClient;
};
