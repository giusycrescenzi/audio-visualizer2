#include "VisualizerWindow.h"
#include <QPainter>
#include <QRandomGenerator>

VisualizerWindow::VisualizerWindow(AudioManager* audioManager, FFTAnalyzer* fftAnalyzer, QWidget* parent)
    : QWidget(parent), audioManager(audioManager), fftAnalyzer(fftAnalyzer) {
    // Start the timer to update the visualization every 16ms (~60 FPS)
    timer = new QTimer(this);

    // Connect the timer's timeout signal to the updateFrame slot
    connect(timer, &QTimer::timeout, this, &VisualizerWindow::updateFrame);

    timer->start(16);  // Update every 16ms (roughly 60 FPS)
    frameCount = 0;
}

VisualizerWindow::~VisualizerWindow() {
    delete timer;
}

void VisualizerWindow::paintEvent(QPaintEvent* event) {
    static float t = 0.0f;
    t += 0.016f;
    static float progress = 0.0f;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 🔳 Sfondo: nero → antracite
    float bgVal = 10 + 5 * (0.5f + 0.5f * std::sin(t * 0.3f));
    painter.fillRect(rect(), QColor(bgVal, bgVal, bgVal));

    float centerX = width() / 2.0f;
    float centerY = height() / 2.0f;
    float artworkY = centerY;
    float formsY   = centerY + 170.0f;

    // 🖼️ Caricamento artwork visibile
    static QImage artwork(QDir(QApplication::applicationDirPath()).filePath("../assets/CanWeKiss.jpg"));
    if (artwork.isNull()) {
        qDebug() << "Immagine non trovata!";
    }

    // Calcola la dimensione per mantenere l'aspect ratio
    QRect imageRect(width() / 4, height() / 6, width() / 2, height() / 3);

    // Calcola il rapporto di proporzione per l'immagine
    float imageAspectRatio = float(artwork.width()) / float(artwork.height());
    int newWidth = imageRect.height() * imageAspectRatio;  // Nuova larghezza per mantenere l'aspect ratio
    int newHeight = imageRect.height();  // Altezza impostata come prima
    QRect finalRect(imageRect.left() + (imageRect.width() - newWidth) / 2, imageRect.top(), newWidth, newHeight);

    // Disegna l'immagine con le nuove dimensioni
    painter.drawImage(finalRect, artwork);

    // Disegna la didascalia sotto l'immagine
    QString caption = "Can We Kiss? ~Giuseppe Crescenzi";  // Modifica con il testo che preferisci
    QFont font("Tahoma", 15, QFont::Bold);  // Font personalizzato
    painter.setFont(font);
    painter.setPen(QPen(QColor(255, 255, 255, 200)));  // Colore del testo (bianco semi-trasparente)

    // Alza la didascalia di 10px
    QRect captionRect(finalRect.left(), finalRect.bottom() - 10, finalRect.width(), 30);
    painter.drawText(captionRect, Qt::AlignCenter, caption);

    // Progress bar
    float progressWidth = progress * width();  // La larghezza della barra in base al progresso

    // Colore della barra di progresso
    QLinearGradient gradient(0, 0, width(), 0);  // Linear gradient orizzontale
    gradient.setColorAt(0, QColor(0, 123, 255));  // Colore blu chiaro
    gradient.setColorAt(1, QColor(0, 92, 191));   // Colore blu scuro

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);  // Non vogliamo bordi per la barra

    // Disegna la barra di progresso
    QRect progressBarRect(width()/4, height() - 426, width()/2, 10);  // Barra alla base
    QRect progressFillRect(progressBarRect.left(), progressBarRect.top(), progressWidth, progressBarRect.height());
    painter.drawRoundedRect(progressFillRect, 5, 5);  // Angoli arrotondati

    // Disegna il bordo della barra di progresso
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(QColor(100, 100, 100), 1));  // Bordo grigio
    painter.drawRoundedRect(progressBarRect, 5, 5);

    // Aumenta il progresso automaticamente
    progress += 1.0f / 50000.0f;  // Incremento del progresso (1 secondo = 1/240)

    if (progress > 1.0f) {
        progress = 1.0f;  // Non superare 1.0f (100%)
    }

    // 🎵 Analisi FFT
    fftAnalyzer->analyze();
    float energy = fftAnalyzer->getCurrentEnergy();

    // 🔵 Cerchi grandi e vibranti
    painter.setPen(QPen(QColor(255, 255, 255, static_cast<int>(100 + 120 * energy)), 1.5));
    painter.setBrush(Qt::NoBrush);
    for (int i = 1; i <= 5; ++i) {
        float base = 90 + i * 100 + 40 * std::sin(t + i);
        float jitter = 60.0f * std::sin(t * 20.0f + i);
        float r = base + jitter;
        painter.drawEllipse(QPointF(centerX, formsY), r * energy, r * energy);
    }

    // 🔺 Triangoli ampi
    for (int i = 0; i < 3; ++i) {
        float angle = t * 0.3f + i * M_PI * 2 / 3;
        float size = 100 + 80 * energy + 5 * std::sin(t * 15 + i);
        QPointF p1(centerX + std::cos(angle) * size, formsY + std::sin(angle) * size);
        QPointF p2(centerX + std::cos(angle + 2.1) * size, formsY + std::sin(angle + 2.1) * size);
        QPointF p3(centerX + std::cos(angle - 2.1) * size, formsY + std::sin(angle - 2.1) * size);
        QPolygonF triangle({p1, p2, p3});
        painter.drawPolygon(triangle);
    }
}
void VisualizerWindow::updateFrame() {
    qDebug() << "Updating frame...";
    // Trigger a repaint every timer event to update the window
    update();  // This will call paintEvent
}