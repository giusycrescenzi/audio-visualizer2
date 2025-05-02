#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QWidget>
#include <QTimer>
#include "AudioManager.h"
#include "FFTAnalyzer.h"

class VisualizerWindow : public QWidget {
    Q_OBJECT

public:
    VisualizerWindow(AudioManager* audioManager, FFTAnalyzer* fftAnalyzer, QWidget* parent = nullptr);
    ~VisualizerWindow();

protected:
    void paintEvent(QPaintEvent* event) override;  // Richiamato ogni volta che serve ridisegnare

    private slots:
        void updateFrame();  // Chiamato dal timer ogni 16 ms (~60 FPS)

private:
    AudioManager* audioManager;
    FFTAnalyzer* fftAnalyzer;
    QTimer timer;  // Timer per aggiornare la finestra periodicamente
};

#endif // VISUALIZERWINDOW_H