#ifndef FFTANALYZER_H
#define FFTANALYZER_H

#include "AudioManager.h"
#include <vector>

class FFTAnalyzer {
public:
    explicit FFTAnalyzer(AudioManager* audioManager);
    ~FFTAnalyzer();

    void analyze();                // Analizza i campioni audio correnti
    float getCurrentEnergy() const; // Ritorna energia normalizzata (0.0 – 1.0)

private:
    AudioManager* audioManager;   // Puntatore alla sorgente audio
    float currentEnergy;          // Energia calcolata (aggiornata ogni frame)
};

#endif // FFTANALYZER_H