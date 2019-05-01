#include "Player.h"

Player::Player(): score(0) {}

void Player::setClientId(int clientId) {
    client_id = clientId;
}

int Player::getClientId() {
    return client_id;
}

int Player::getScore() const {
    return score;
}

void Player::addPoints(int points) {
    score += points;
}

bool operator < (const Player &player1, const Player &player2) {
    return player1.getScore() < player2.getScore();
}
