# Taboo Network
* This program creates a network game of Taboo
* This project uses the open frameworks libraries: ofxNetwork, ofxSoundPlayer and ofxGui

**Rules**
* Starting screen will show whether you are a describer or a guesser
    * Describer must press 's' for the round to begin
* Describer
    * Player has 60 seconds to describe as many cards as possible
    * Type clues for the given word into the text field and press enter to send to the guessers
        * Cannot use restricted words or the actual word, otherwise the card will automatically switch
    * Press space to skip a card, make sure you're not still in the text field
    * One point for each card that a guesser can accurately guess
* Guesser
    * Player has 60 seconds to guess as many cards as possible
    * Type guess into text field and press enter to guess
        * If correct a bell noise will sound and will move to next card
    * Two points for each accurately guessed card

**Build Instructions**
* Make sure you have openframeworks installed
* Clone this repository
* Using the project generator, click on import
    * There are two different projects, server and client. Make sure you import them seperately
    * For client add ofxGui and ofxNetwork to the addons
    * For server add ofxNetwork
* Click on generate and open in IDE for both client and server. 
* Run the server first
* Through the terminal, go into TabooClient and then bin
    * Run open -n TabooClientDebug.app multiple times depending on how many players you want
