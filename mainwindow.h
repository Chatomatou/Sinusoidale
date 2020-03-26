#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>
#include <QPainter>
#include <QtMath>
#include <qDebug>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent* event);

private:
    QWidget* m_wCentral;
    QFormLayout* m_menu;

    QLineEdit* m_frequency;
    QLineEdit* m_amplitude;
    QLineEdit* m_pulsation;
    QLineEdit* m_phaseShift;
    QLineEdit* m_period;
};
#endif // MAINWINDOW_H
