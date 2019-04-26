**Week 1**
* Create Card class 
* Add ofxGui to Project 
* Create a vector of cards from a file using ofstream
* Create a timer
    * Couldn't figure out how to create a timer, tried to find an addon.
    * Use getElapsedTime to create my own timer
**Week 2**
* Implement ofxNetworks into project
    * Split into two projects. Client and server and add those files to github
    * Clients have unique ids and server uses this to identify and send information
    * Create variables to keep track of state and words sent from server to the current player client
* Create textbox
    * Try to use ofxUIUtils to create textbook, but had many errors
    * Try to use simpleTextBuffer addon to create textbox, but textbox took over whole screen, and text went on top of taboo card
    * Resort to using textField already in open frameworks
* Issues
    * Word and restricted word variables are initialized in client, but do not show up on screen
    * Timer uses getElapsedTime but it does not create an accurate timer
