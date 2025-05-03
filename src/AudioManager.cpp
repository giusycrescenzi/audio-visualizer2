#include "AudioManager.h"
#include <cstdint>

AudioManager::AudioManager() : AudioManager(sf::SoundBuffer()) {
}
AudioManager::AudioManager(const sf::SoundBuffer& buffer) : buffer(buffer), player(buffer) {
}
AudioManager::~AudioManager() = default;

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

const sf::Sound& AudioManager::getPlayer() const {
    return player;
}
float AudioManager::getSample(int index) const {
    const std::int16_t* samples = buffer.getSamples();
    if (index >= buffer.getSampleCount()) return 0.0f;
    return static_cast<float>(samples[index]) / 32768.0f;  // normalizza tra -1.0 e +1.0
}