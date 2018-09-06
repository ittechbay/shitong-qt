#ifndef FTSCMDTHREAD_H
#define FTSCMDTHREAD_H

#include <QThread>

class FtsCmdThread : public QThread
{
    Q_OBJECT
public:
    FtsCmdThread(QObject *parent);
    ~FtsCmdThread();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize);

signals:
    void pwrErr(int slot, int error);
    void ntpErr(int slot, int error);
    void gnssErr(int slot, int error);

protected:
    void run();

/*private:
    uint rgbFromWaveLength(double wave);

    QMutex mutex;
    QWaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart;
    bool abort;

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];*/
};

#endif // FTSCMDTHREAD_H
