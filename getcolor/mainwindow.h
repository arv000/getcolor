#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include "qpickwidget.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *m_ptrWdgMain;
    QVBoxLayout *m_ptrLayoutMain;
    QHBoxLayout *m_ptrLayoutShowColor;
    QHBoxLayout *m_ptrLayoutRed;
    QHBoxLayout *m_ptrLayoutGreen;
    QHBoxLayout *m_ptrLayoutBlue;
    QHBoxLayout *m_ptrLayoutButton;

    QLabel *m_ptrLabShowColor;

    QLabel *m_ptrLabRed;
    QLabel *m_ptrLabGreen;
    QLabel *m_ptrLabBlue;

    QSlider *m_ptrSliderRed;
    QSlider *m_ptrSliderGreen;
    QSlider *m_ptrSliderBlue;

    QLabel *m_ptrLabShowRed;
    QLabel *m_ptrLabShowGreen;
    QLabel *m_ptrLabShowBlue;

    QLineEdit *m_ptrLineRed;
    QLineEdit *m_ptrLineGreen;
    QLineEdit *m_ptrLineBlue;

    int m_iRed;
    int m_iGreen;
    int m_iBulle;

    QPushButton *m_ptrBtnPickColor;
    QPushButton *m_ptrBtnCopy;
    QLineEdit *m_ptrLineColor;
    QPickWidget *m_ptrWdgPick;
    enum ColorType{
           Red,
            Green,
            Blue

    };
   private:
    void initUI();
    QLabel *updateShowLable(QLabel *label, Qt::GlobalColor color);
    void updateLable( int value,ColorType type);
    QSlider *updateSlider(QSlider *slider);
    void initConnect();
    void updateShowColor();

   public slots:
    void slotRedValue(int value);
    void slotGreenValue(int value);
    void slotBlueValue(int value);
    void slotPickColor();
    void slotShowPick();
    void slotCopyColorValue();
    void slotClosePickWidget(int);
    void slotGetColor(int r, int g, int b);
    void slotRedValueChange(QString strValue);
    void slotGreenValueChange(QString strValue);
    void slotBlueValueChange(QString strValue);
    // QWidget interface
   protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif  // MAINWINDOW_H
