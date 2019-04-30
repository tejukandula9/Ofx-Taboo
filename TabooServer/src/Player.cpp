#include "Player.h"

Player::Player(): score(0) {}

void Player::setClientId(int clientId) {
    client_id = clientId;
}

int Player::getClientId() {
    return client_id;
}

int Player::getScore() {
    return score;
}

void Player::addPoints(int points) {
    score += points;
}
