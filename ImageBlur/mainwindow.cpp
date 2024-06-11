#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImageReader>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel(this);
    blurSlider = new QSlider(Qt::Horizontal, this);
    openButton = new QPushButton("Open Image", this);

    blurSlider->setRange(0, 10);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(blurSlider);
    layout->addWidget(openButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(blurSlider, &QSlider::valueChanged, this, &MainWindow::updateBlur);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        sourceImage.load(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(sourceImage).scaled(imageLabel->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::updateBlur(int value)
{
    if (!sourceImage.isNull()) {
        QImage blurredImage = blurImage(sourceImage, value);
        imageLabel->setPixmap(QPixmap::fromImage(blurredImage).scaled(imageLabel->size(), Qt::KeepAspectRatio));
    }
}

QImage MainWindow::blurImage(const QImage &source, int blurRadius)
{
    if (source.isNull() || blurRadius == 0) {
        return source;
    }

    QImage result(source.size(), QImage::Format_ARGB32);
    QGraphicsScene scene;
    QGraphicsPixmapItem item;

    item.setPixmap(QPixmap::fromImage(source));
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);

    scene.addItem(&item);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));

    return result;
}
