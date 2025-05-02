#include <SFML/Audio.hpp>

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QWidget>
#include <SFML/Audio.hpp>
#include <iostream>

class MusicVisualizer : public QMainWindow {
    Q_OBJECT

public:
    MusicVisualizer(QWidget *parent = nullptr) : QMainWindow(parent) {
        auto *central = new QWidget(this);
        auto *layout = new QVBoxLayout(central);

        auto *button = new QPushButton("Choose and Play MP3", this);
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, &MusicVisualizer::loadAndPlayMusic);

        setCentralWidget(central);
        setWindowTitle("MusicArt2");
        resize(400, 200);
    }

private:
    sf::Music music;

    void loadAndPlayMusic() {
        QString file = QFileDialog::getOpenFileName(
            this,
            "Open MP3 File",
            QDir::homePath(),
            "Audio Files (*.mp3)"
        );

        if (!file.isEmpty()) {
            if (!music.openFromFile(file.toStdString())) {
                std::cerr << "Failed to open " << file.toStdString() << std::endl;
                return;
            }
            music.play();
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MusicVisualizer window;
    window.show();
    return app.exec();
}

/*int main() {
    // Carica il buffer audio da un file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("suono.wav")) {
        // Gestione dell'errore
        return -1;
    }

    // Crea un oggetto Sound e associa il buffer
    sf::Sound sound;
    sound.setBuffer(buffer);

    // Riproduci il suono
    sound.play();

    // Attendi che il suono termini
    while (sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}*/