#include <QApplication>
#include "VisualizerWindow.h"
#include "AudioManager.h"
#include "FFTAnalyzer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Application started";

    // ✅ Percorso assoluto del file .wav da riprodurre e visualizzare
    const std::string filePath = "/Users/giuseppecrescenzi/Desktop/pezzi/HOUSE/wav/Can We Kiss (tonight).wav";

    // ✅ Istanzia e riproduci audio
    auto* audioManager = new AudioManager();
    if (!audioManager->play(filePath)) {
        qCritical("Errore nel caricamento o nella riproduzione dell'audio.");
        return -1;
    }

    // ✅ Crea l'analizzatore FFT con l'audio manager
    auto* fftAnalyzer = new FFTAnalyzer(audioManager);

    // ✅ Crea e mostra la finestra di visualizzazione
    auto* visualizer = new VisualizerWindow(audioManager, fftAnalyzer);
    visualizer->resize(800, 600);
    visualizer->show();

    return app.exec();
}