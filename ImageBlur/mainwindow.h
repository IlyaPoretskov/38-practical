#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void updateBlur(int value);

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QSlider *blurSlider;
    QPushButton *openButton;
    QImage sourceImage;

    QImage blurImage(const QImage &source, int blurRadius);
};

#endif // MAINWINDOW_H
