#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp {
    string current_state;
    string current_word;
    vector<string> restricted;
    vector<string> clues;
    string description;
    string guess;
    string score;
    string describer_move;
    string last_description;
    float timer_length;
    bool started_round;
    
    /**
     *These two variables are the length of the actual words "WORD:" AND "RESTRICTED:" used to parse the Card string recieved from server
     **/
    int word_length;
    int restricted_length;
    
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
    void checkInput();
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
