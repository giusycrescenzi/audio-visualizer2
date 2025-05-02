#include "VisualizerWindow.h"
#include <QPainter>
#include <cstdlib>

VisualizerWindow::VisualizerWindow(AudioManager* audioMgr, FFTAnalyzer* fftAnlz, QWidget* parent)
    : QWidget(parent), audioManager(audioMgr), fftAnalyzer(fftAnlz) {

    setFixedSize(800, 600);  // Dimensione fissa della finestra
    setStyleSheet("background-color: black;");  // Sfondo nero

    connect(&timer, &QTimer::timeout, this, &VisualizerWindow::updateFrame);
    timer.start(16);  // 60 FPS = ogni 16 ms
}

VisualizerWindow::~VisualizerWindow() {}

void VisualizerWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Grafica più fluida

    float energy = fftAnalyzer->getCurrentEnergy();  // Valore 0.0–1.0

    // Disegna un cerchio centrato, la cui dimensione dipende dall'energia
    int radius = static_cast<int>(energy * 300.0f);  // Es: 0.5 = 150px

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(width()/2 - radius/2, height()/2 - radius/2, radius, radius);
}

void VisualizerWindow::updateFrame() {
    fftAnalyzer->analyze();  // Calcola energia da audio
    update();                // Triggera paintEvent()
}