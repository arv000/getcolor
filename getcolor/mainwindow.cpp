#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QClipboard>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget(this))
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrLayoutShowColor(new QHBoxLayout)
    , m_ptrLayoutRed(new QHBoxLayout)
    , m_ptrLayoutGreen(new QHBoxLayout)
    , m_ptrLayoutBlue(new QHBoxLayout)
    , m_ptrLayoutButton(new QHBoxLayout)
    , m_ptrLabShowColor(new QLabel(m_ptrWdgMain))
    , m_ptrLabRed(new QLabel(m_ptrWdgMain))
    , m_ptrLabGreen(new QLabel(m_ptrWdgMain))
    , m_ptrLabBlue(new QLabel(m_ptrWdgMain))
    , m_ptrSliderRed(new QSlider(m_ptrWdgMain))
    , m_ptrSliderGreen(new QSlider(m_ptrWdgMain))
    , m_ptrSliderBlue(new QSlider(m_ptrWdgMain))
    , m_ptrLabShowRed(new QLabel(m_ptrWdgMain))
    , m_ptrLabShowGreen(new QLabel(m_ptrWdgMain))
    , m_ptrLabShowBlue(new QLabel(m_ptrWdgMain))
    , m_ptrLineRed(new QLineEdit("0", m_ptrWdgMain))
    , m_ptrLineGreen(new QLineEdit("0", m_ptrWdgMain))
    , m_ptrLineBlue(new QLineEdit("0", m_ptrWdgMain))
    , m_iRed(0)
    , m_iGreen(0)
    , m_iBulle(0)
    , m_ptrBtnPickColor(new QPushButton("选择", m_ptrWdgMain))
    , m_ptrBtnCopy(new QPushButton("复制", m_ptrWdgMain))
    , m_ptrLineColor(new QLineEdit(m_ptrWdgMain))
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    setWindowTitle("取色器");
    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    m_ptrLabShowColor = updateShowLable(m_ptrLabShowColor, Qt::black);
    m_ptrLabShowColor->setFixedSize(50, 50);
    m_ptrLayoutShowColor->addWidget(m_ptrLabShowColor);

    m_ptrLabShowRed = updateShowLable(m_ptrLabShowRed, Qt::black);
    m_ptrSliderRed = updateSlider(m_ptrSliderRed);
    m_ptrLabRed = updateShowLable(m_ptrLabRed, Qt::red);
    m_ptrLayoutRed->addWidget(m_ptrLabShowRed);
    m_ptrLayoutRed->addWidget(m_ptrSliderRed);
    m_ptrLayoutRed->addWidget(m_ptrLabRed);
    m_ptrLayoutRed->addWidget(m_ptrLineRed);
    m_ptrLineRed->setPlaceholderText("0-255");
    m_ptrLineRed->setText("0");

    m_ptrLabShowGreen = updateShowLable(m_ptrLabShowGreen, Qt::black);
    m_ptrSliderGreen = updateSlider(m_ptrSliderGreen);
    m_ptrLabGreen = updateShowLable(m_ptrLabGreen, Qt::green);
    m_ptrLayoutGreen->addWidget(m_ptrLabShowGreen);
    m_ptrLayoutGreen->addWidget(m_ptrSliderGreen);
    m_ptrLayoutGreen->addWidget(m_ptrLabGreen);
    m_ptrLayoutGreen->addWidget(m_ptrLineGreen);
    m_ptrLineGreen->setPlaceholderText("0-255");
    m_ptrLineGreen->setText("0");

    m_ptrLabShowBlue = updateShowLable(m_ptrLabShowBlue, Qt::black);
    m_ptrSliderBlue = updateSlider(m_ptrSliderBlue);
    m_ptrLabBlue = updateShowLable(m_ptrLabBlue, Qt::blue);
    m_ptrLayoutBlue->addWidget(m_ptrLabShowBlue);
    m_ptrLayoutBlue->addWidget(m_ptrSliderBlue);
    m_ptrLayoutBlue->addWidget(m_ptrLabBlue);
    m_ptrLayoutBlue->addWidget(m_ptrLineBlue);
    m_ptrLineBlue->setPlaceholderText("0-255");
    m_ptrLineBlue->setText("0");

    m_ptrLayoutButton->addWidget(m_ptrBtnPickColor);
    m_ptrLayoutButton->addWidget(m_ptrBtnCopy);
    m_ptrLayoutButton->addWidget(m_ptrLineColor);
    m_ptrLineColor->setPlaceholderText("6位16进制");
    m_ptrLayoutMain->addLayout(m_ptrLayoutShowColor);
    m_ptrLayoutMain->addLayout(m_ptrLayoutRed);
    m_ptrLayoutMain->addLayout(m_ptrLayoutGreen);
    m_ptrLayoutMain->addLayout(m_ptrLayoutBlue);
    m_ptrLayoutMain->addLayout(m_ptrLayoutButton);

    this->setCentralWidget(m_ptrWdgMain);
}

QLabel *MainWindow::updateShowLable(QLabel *label, Qt::GlobalColor color)
{
    label->setFixedSize(15, 15);
    label->setAutoFillBackground(true);
    label->setPalette(QPalette(QPalette::Background, QColor(color)));
    return label;
}

void MainWindow::updateLable(int value, ColorType type)
{
    switch (type) {
        case Red:
            m_ptrLabShowRed->setPalette(
                QPalette(QPalette::Background, QColor(value, 0, 0)));
            break;

        case Green:
            m_ptrLabShowGreen->setPalette(
                QPalette(QPalette::Background, QColor(0, value, 0)));
            break;
        case Blue:
            m_ptrLabShowBlue->setPalette(
                QPalette(QPalette::Background, QColor(0, 0, value)));
            break;
    }
}

QSlider *MainWindow::updateSlider(QSlider *slider)
{
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMaximum(255);
    slider->setMinimum(0);
    return slider;
}

void MainWindow::initConnect()
{
    connect(m_ptrSliderRed, SIGNAL(valueChanged(int)), this,
            SLOT(slotRedValue(int)));
    connect(m_ptrSliderGreen, SIGNAL(valueChanged(int)), this,
            SLOT(slotGreenValue(int)));
    connect(m_ptrSliderBlue, SIGNAL(valueChanged(int)), this,
            SLOT(slotBlueValue(int)));
    connect(m_ptrBtnPickColor, SIGNAL(clicked()), this, SLOT(slotPickColor()));
    connect(m_ptrBtnCopy, SIGNAL(clicked()), this, SLOT(slotCopyColorValue()));
    //    connect(m_ptrWdgPick, SIGNAL(finished(int)), this,
    //            SLOT(slotClosePickWidget(int)));
    //    connect(m_ptrWdgPick, &QPickWidget::sigColor, this,
    //            &MainWindow::slotGetColor);
    connect(m_ptrLineRed, SIGNAL(textChanged(QString)), this,
            SLOT(slotRedValueChange(QString)));
    connect(m_ptrLineGreen, SIGNAL(textChanged(QString)), this,
            SLOT(slotGreenValueChange(QString)));
    connect(m_ptrLineBlue, SIGNAL(textChanged(QString)), this,
            SLOT(slotBlueValueChange(QString)));

    // 绑定回车
    connect(m_ptrLineColor, &QLineEdit::returnPressed, this, [this]() {
        QString strColor = m_ptrLineColor->text();
        if (strColor.size() != 6) {
            return;
        }
        QColor color("#" + strColor);

        m_ptrLineRed->setText(QString::number(color.red()));
        m_ptrLineGreen->setText(QString::number(color.green()));
        m_ptrLineBlue->setText(QString::number(color.blue()));
        qInfo() << "m_ptrLineColor" << m_ptrLineColor->text();
    });
}

void MainWindow::updateShowColor()
{
    m_ptrLabShowColor->setPalette(
        QPalette(QPalette::Background, QColor(m_iRed, m_iGreen, m_iBulle)));
    QString strRed = QString("%1").arg(m_iRed, 2, 16, QLatin1Char('0'));
    QString strGreen = QString("%1").arg(m_iGreen, 2, 16, QLatin1Char('0'));
    QString strBlue = QString("%1").arg(m_iBulle, 2, 16, QLatin1Char('0'));
    m_ptrLineColor->setText(strRed + strGreen + strBlue);
}

void MainWindow::slotRedValue(int value)
{
    m_ptrLineRed->setText(QString::number(value));
    m_iRed = value;
    updateLable(value, Red);
    updateShowColor();
}

void MainWindow::slotGreenValue(int value)
{
    m_ptrLineGreen->setText(QString::number(value));
    m_iGreen = value;
    updateLable(value, Green);
    updateShowColor();
}

void MainWindow::slotBlueValue(int value)
{
    m_ptrLineBlue->setText(QString::number(value));
    m_iBulle = value;
    updateLable(value, Blue);
    updateShowColor();
}

void MainWindow::slotPickColor()
{
    m_currentPoint = this->geometry();
    this->hide();

    QTimer::singleShot(200, this, &MainWindow::slotShowPick);
}

void MainWindow::slotShowPick()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QList<QScreen *> list = QGuiApplication::screens();
    for (auto item : m_listPtrWdgPick) {
        delete item;
        item = nullptr;
    }
    m_listPtrWdgPick.clear();
    for (auto item : list) {
        auto temp = new QPickWidget();
        temp->setPickPicture(item->grabWindow(0));
        temp->move(item->geometry().x(), item->geometry().y());
        temp->show();
        connect(temp, SIGNAL(finished(int)), this,
                SLOT(slotClosePickWidget(int)));
        connect(temp, &QPickWidget::sigColor, this, &MainWindow::slotGetColor);
        temp->showFullScreen();
        m_listPtrWdgPick.push_back(temp);
    }
}

void MainWindow::slotCopyColorValue()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(m_ptrLineColor->text());
}

void MainWindow::slotClosePickWidget(int)
{
    for (auto item : m_listPtrWdgPick) {
        item->close();
    }

    this->show();
    this->setGeometry(m_currentPoint);
    this->move(m_currentPoint.x(), m_currentPoint.y());
    qInfo() << "slotClosePickWidget";
}

void MainWindow::slotGetColor(int r, int g, int b)
{
    qInfo() << "r=" << r;
    qInfo() << "g=" << g;
    qInfo() << "b=" << b;
    m_ptrLabShowColor->setPalette(
        QPalette(QPalette::Background, QColor(r, g, b)));
    m_ptrLineRed->setText(QString::number(r));
    m_ptrLineGreen->setText(QString::number(g));
    m_ptrLineBlue->setText(QString::number(b));
    m_ptrSliderRed->setValue(r);
    m_ptrSliderGreen->setValue(g);
    m_ptrSliderBlue->setValue(b);
}

void MainWindow::slotRedValueChange(QString strValue)
{
    m_ptrSliderRed->setValue(strValue.toInt());
}

void MainWindow::slotGreenValueChange(QString strValue)
{
    m_ptrSliderGreen->setValue(strValue.toInt());
}

void MainWindow::slotBlueValueChange(QString strValue)
{
    m_ptrSliderBlue->setValue(strValue.toInt());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        qInfo() << "keyPressEvent";
    }
}
