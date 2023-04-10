#include "qpickwidget.h"
#include <QKeyEvent>
#include <QtDebug>
#include <QBrush>
#include <QPalette>
#include <QRgb>
QPickWidget::QPickWidget(QWidget *parent)
    : QDialog(parent)
    , m_ptrLabMouse(new QLabel(this))
{
    m_ptrLabMouse->setFixedSize(100, 100);
    m_ptrLabMouse->setAutoFillBackground(true);
    m_ptrLabMouse->setPalette(QPalette(QPalette::Background, QColor(Qt::red)));
    m_ptrLabMouse->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setMouseTracking(true);
    setCursor(Qt::CrossCursor);
    initConnect();
}

void QPickWidget::setPickPicture(QPixmap pixmap)
{
    m_pixmapPickPicture = pixmap;
    QPalette p;
    p.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(p);
}

void QPickWidget::initConnect()
{
    // connect(this, SIGNAL(clicked()), this, SLOT(slotPickColor));
}

void QPickWidget::slotPickColor() { this->close(); }

void QPickWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
}

void QPickWidget::showEvent(QShowEvent *event) { qInfo() << "showEvent"; }

void QPickWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mouse_x = event->x();
    int mouse_y = event->y();

    qInfo() << mouse_x << " " << mouse_y << " " << QCursor::pos();
    m_ptrLabMouse->move(mouse_x - m_ptrLabMouse->width() / 2,
                        mouse_y - m_ptrLabMouse->height() / 2);

    QPixmap cropped = m_pixmapPickPicture.copy(mouse_x - 4, mouse_y - 4, 9, 9);
    QPixmap cropped1 = cropped.scaled(100, 100, Qt::KeepAspectRatio);

    QPalette p;
    p.setBrush(QPalette::Background, QBrush(cropped1));
    m_ptrLabMouse->setPalette(p);
}

void QPickWidget::mousePressEvent(QMouseEvent *event)
{
    qInfo() << "mousePressEvent";
    QRgb tmp_rgb = m_pixmapPickPicture.toImage().pixel(event->x(), event->y());
    QColor rgb(tmp_rgb);
    emit sigColor(rgb.red(), rgb.green(), rgb.blue());
    this->close();
}
