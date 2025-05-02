#include "AudioManager.h"

AudioManager::AudioManager() {}

AudioManager::~AudioManager() {}

bool AudioManager::play(const std::string& filename) {
    if (!buffer.loadFromFile(filename))
        return false;               // Fallimento: file audio non trovato o non valido

    player.setBuffer(buffer);      // Collega i dati audio al player
    player.play();                 // Parte la riproduzione
    return true;
}

const sf::SoundBuffer& AudioManager::getBuffer() const {
    return buffer;
}

const sf::SoundBufferPlayer& AudioManager::getPlayer() const {
    return player;
}