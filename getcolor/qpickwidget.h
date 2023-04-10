#ifndef QPICKWIDGET_H
#define QPICKWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
class QPickWidget : public QDialog {
    Q_OBJECT
   public:
    explicit QPickWidget(QWidget *parent = nullptr);
    void setPickPicture(QPixmap pixmap);
    QPixmap m_pixmapPickPicture;
    // 放大镜效果控件
    QLabel *m_ptrLabMouse;
    void initConnect();
   signals:
    void sigColor(int r, int g, int b);
   public slots:
    void slotPickColor();
    // QWidget interface
   protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif  // QPICKWIDGET_H
