#include "FFTAnalyzer.h"
#include <cmath>
#include <iostream>

FFTAnalyzer::FFTAnalyzer(AudioManager* audioMgr)
    : audioManager(audioMgr), currentEnergy(0.0f) {

    const int numSamples = 1024;
    audioSamples.resize(numSamples);

    // ✅ Alloca fftResult con fftw_malloc
    fftResult = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * numSamples));

    // ✅ Crea piano FFT
    fftPlan = fftw_plan_dft_r2c_1d(numSamples, audioSamples.data(), fftResult, FFTW_ESTIMATE);
}

FFTAnalyzer::~FFTAnalyzer() {
    fftw_destroy_plan(fftPlan);
    fftw_free(fftResult);  // ✅ Libera fftResult
}

void FFTAnalyzer::analyze() {
    const int numSamples = static_cast<int>(audioSamples.size());

    // ✅ Ottieni samples dall'AudioManager
    for (int i = 0; i < numSamples; ++i) {
        audioSamples[i] = audioManager->getSample(i);  // Implementa questo metodo in AudioManager
    }

    fftw_execute(fftPlan);  // ✅ Esegui FFT

    currentEnergy = 0.0f;
    for (int i = 0; i < numSamples / 2; ++i) {
        const double real = fftResult[i][0];
        const double imag = fftResult[i][1];
        currentEnergy += static_cast<float>(real * real + imag * imag);
    }

    currentEnergy = std::min(currentEnergy / numSamples, 1.0f);
}

float FFTAnalyzer::getCurrentEnergy() const {
    return currentEnergy;
}