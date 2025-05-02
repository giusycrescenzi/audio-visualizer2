#include "FFTAnalyzer.h"
#include <cstdlib> // solo per simulazione random

FFTAnalyzer::FFTAnalyzer(AudioManager* audioMgr)
    : audioManager(audioMgr), currentEnergy(0.0f) {}

FFTAnalyzer::~FFTAnalyzer() {}

void FFTAnalyzer::analyze() {
    // 👇 AL MOMENTO: energia falsa generata a caso
    currentEnergy = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float FFTAnalyzer::getCurrentEnergy() const {
    return currentEnergy;
}