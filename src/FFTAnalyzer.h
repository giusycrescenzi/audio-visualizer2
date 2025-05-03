#ifndef FFTANALYZER_H
#define FFTANALYZER_H

#include "AudioManager.h"
#include <vector>
#include <fftw3.h>

class FFTAnalyzer {
public:
    explicit FFTAnalyzer(AudioManager* audioManager);
    ~FFTAnalyzer();

    void analyze();
    float getCurrentEnergy() const;

private:
    AudioManager* audioManager;
    float currentEnergy;

    std::vector<double> audioSamples;
    fftw_complex* fftResult;   // ✅ Usato con fftw_malloc
    fftw_plan fftPlan;
};

#endif // FFTANALYZER_H