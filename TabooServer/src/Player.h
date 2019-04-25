#include <string>

class Player {
    std::string name;
    int score;
    std::string id;
    int client_id;
    
public:
    Player();
    Player(std::string player_name, std::string player_id, int cId);
    
    void setId(std::string Pid);
    void setClientId(int clientId);
    std::string getName();
    std::string getId();
    int getClientId();
    int getScore();
    void addPoints(int points);
};
