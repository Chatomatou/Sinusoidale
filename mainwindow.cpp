#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << QCoreApplication::applicationDirPath();

    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/ressources/app.png"));

    m_wCentral = new QWidget;

    m_frequency = new QLineEdit;
    m_amplitude = new QLineEdit;
    m_pulsation = new QLineEdit;
    m_phaseShift = new QLineEdit;
    m_period = new QLineEdit;

    m_pulsation->setEnabled(false);
    m_period->setEnabled(false);

    m_menu = new QFormLayout;

    m_menu->addRow("&A (Vcc)", m_amplitude);
    m_menu->addRow("&Frequency (Hz)", m_frequency);
    m_menu->addRow("&Periodicity (s)", m_period);
    m_menu->addRow("&ω Pulsation (rad/s)", m_pulsation);
    m_menu->addRow("&φ Phase Shift", m_phaseShift);

    m_amplitude->setText("1");
    m_frequency->setText("1");
    m_phaseShift->setText("0");

    m_wCentral->setLayout(m_menu);

    QObject::connect(m_amplitude, &QLineEdit::textChanged, this, [this](){
        if(m_amplitude->text().toInt() < 0)
            m_amplitude->setText("0");

        if(m_amplitude->text().toInt() > 100)
            m_amplitude->setText("100");

        update();
    });

    QObject::connect(m_frequency, &QLineEdit::textChanged, this, [this](){
        if(m_frequency->text().toInt() < 0)
            m_frequency->setText("1");

        if(m_frequency->text().toInt() > 100)
            m_frequency->setText("100");
        update();
    });

    QObject::connect(m_phaseShift, &QLineEdit::textChanged, this, [this](){update();});

    setCentralWidget(m_wCentral);
    setFixedSize(1200, 600);


}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent* event)
{
    (void)event;
    QPainter pen(this);

    qint32 amplitude = m_amplitude->text().toInt();
    qint32 frequency = m_frequency->text().toInt();
    qint32 phaseShift = m_phaseShift->text().toInt();

    double pulsation = 2 * M_PI * frequency;
    double period = (frequency == 0) ? 0 : 1 / static_cast<double>(frequency);

    m_pulsation->setText(QString::number(pulsation));
    m_period->setText(QString::number(period));


    pen.setPen(Qt::black);
    pen.setBrush(Qt::red);

    pen.drawLine(0, 200, width(), 200);
    pen.drawLine(0, height() - 200, width(), height() - 200);

    double beforeY = 0;

    for(auto t = 0; t < width(); t++)
    {
        auto y = amplitude * qSin(pulsation * t * 0.004 + phaseShift);
        auto x = t;

        if(t == 0)
        {
            pen.drawPoint(x, static_cast<int>(height() - 200 - 200 / 2 - y));
            beforeY = y;
        }
        else
        {
            pen.drawLine(x - 1, static_cast<int>(height() - 200 - 200 / 2 - beforeY), x, static_cast<int>(height() - 200 - 200 / 2 - y));
            beforeY = y;
        }
    }


}

