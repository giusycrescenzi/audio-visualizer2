#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QDir>
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include "AudioManager.h"
#include "FFTAnalyzer.h"

class VisualizerWindow : public QWidget {
    Q_OBJECT

public:
    VisualizerWindow(AudioManager* audioManager, FFTAnalyzer* fftAnalyzer, QWidget* parent = nullptr);
    ~VisualizerWindow() override;

protected:
    void paintEvent(QPaintEvent* event) override;  // This is where we draw the random visualization

    private slots:
        void updateFrame();  // This is the slot for the timer event

private:
    AudioManager* audioManager;
    FFTAnalyzer* fftAnalyzer;
    QTimer* timer;  // Timer for regular updates
    int frameCount;
};

#endif // VISUALIZERWINDOW_H