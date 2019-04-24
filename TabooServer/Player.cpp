#include "Player.h"

Player::Player() {
    score = 0;
}

Player::Player(std::string player_name, std::string player_id, int cId) {
    score = 0;
    name = player_name;
    id = player_id;
    client_id = cId;
}

void Player::setId(std::string Pid) {
    id = Pid;
}

void Player::setClientId(int clientId) {
    client_id = clientId;
}

std::string Player::getName() {
    return name;
}

std::string Player::getId() {
    return id;
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
