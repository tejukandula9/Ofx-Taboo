#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTextBox.h"
#include "Card.h"


extern vector<Card> cards;
extern int current_card;

class ofApp : public ofBaseApp{
    
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
    
    ofxPanel gui;
    
    ofxButton skipButton;
    ofTrueTypeFont wordFont;
    ofTrueTypeFont restrictedFont;
    ofTrueTypeFont timerFont;
    ofxTextField textField;
    ofSoundPlayer errorSound;
    
    float time;
};
