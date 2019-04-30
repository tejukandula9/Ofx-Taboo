#include <string>

class Player {
    int score;
    int client_id;
    
public:
    Player();
    
    void setClientId(int clientId);
    int getClientId();
    int getScore();
    void addPoints(int points);
};
