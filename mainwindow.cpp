#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->m_layout = new QHBoxLayout(this->centralWidget());
    this->m_qSwitch = new MQSwitch(this->centralWidget());
    this->m_qSwitch->setFixedWidth(100);
    this->m_layout->addWidget(this->m_qSwitch);

    connect(this->m_qSwitch, &MQSwitch::toggled, [this](bool checked) {
        qDebug() << "MQSwitch checked is" << checked;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

