#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    editor = new QPlainTextEdit(this);
    webView = new QWebEngineView(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(editor);
    layout->addWidget(webView);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::updateWebView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWebView()
{
    QString html = editor->toPlainText();
    webView->setHtml(html);
}
