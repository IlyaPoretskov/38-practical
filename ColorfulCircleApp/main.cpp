#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QUrl>

class RedButtonApp : public QWidget {
    Q_OBJECT

public:
    RedButtonApp(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *button = new QPushButton("Press Me", this);
        button->setStyleSheet("background-color: red; color: white; font-size: 18px;");
        layout->addWidget(button);
        setLayout(layout);

        player = new QMediaPlayer(this);
        player->setMedia(QUrl("qrc:/resources/click_sound.mp3"));

        connect(button, &QPushButton::pressed, this, &RedButtonApp::playSound);
    }

private slots:
    void playSound() {
        player->play();
    }

private:
    QMediaPlayer *player;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RedButtonApp window;
    window.setFixedSize(200, 150);
    window.show();

    return app.exec();
}
