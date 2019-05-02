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
* Design guessing part of the game
    * Send description from describing player to guessing player and display it on screen
    * Send guesses to the client to check if they are the right word
    * Still have to figure out how to run two instances of the client to test the whole game
* Issues
    * There appears to be a lag sending things to the client, so the restricted words don't match the actual words
    * Timer uses getElapsedTime but it does not create an accurate timer
    
**Week 3**
* Fixed Issues from Week 2
    * To fix the lag, I sent the actual word and the restricted words as one long string instead of sending the actual word and each restricted word seperately
    * I used ofResetElapsedTimeCounter() to reset the time at the begenning of each round
* Create helper method to parse through a card string to determine actual and restricted words.
* Create a helper function that turns the description/guess from the textfield to uppercase before sending it to the sender. This helps make it easier to check against the actual words in the card class since they are all uppercase
* Create a boolean variable to check when a round is started
* Add sounds when a restricted word is used, time is up or someone guessed the correct word
* Rank players in the client and send current rankings to servers to display before the start of each round
* Issues and Fixes
    * Vector of clues was getting infinately long
        * Check to see if the clue had been used before or is empty before adding to the vector
    * End round was incrementing player twice
        * Only send the command to end round from the describer, not any of the guessers
    * The guesses and clues entered from the previous round were showing up in the new round
        * Clear clues and guesses vector at the start of each round
