#include <string>

class Player {
    int score;
    int client_id;
    int ranking;
    
public:
    Player();
    
    void setClientId(int clientId);
    int getClientId();
    int getScore() const;
    int getRanking();
    void addPoints(int points);
};

// Used to sort array by players score 
bool operator < (const Player &player1, const Player &player2);
