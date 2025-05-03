#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H


#include <SFML/Audio.hpp>
#include <string>

class AudioManager {
public:
    AudioManager();      
    explicit AudioManager(const sf::SoundBuffer& buffer);                  // Costruttore: inizializza
    ~AudioManager();                       // Distruttore: pulizia

    bool play(const std::string& filename); // Carica e riproduce un file audio
    const sf::SoundBuffer& getBuffer() const;  // Ritorna il buffer (solo lettura)
    const sf::Sound& getPlayer() const; // Ritorna il player (solo lettura)
    float getSample(int index) const;

private:
    sf::SoundBuffer buffer;               // Dati audio in RAM
    sf::Sound player;         // Oggetto che riproduce il suono
};

#endif // AUDIOMANAGER_H