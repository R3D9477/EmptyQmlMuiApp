#ifndef BGRMAIN_H
#define BGRMAIN_H

#include <QObject>

class BGRMain: public QObject
{
    //...
    //...

    Q_OBJECT

signals:

    //...
    //...

public:

    explicit BGRMain(QObject *parent = nullptr);
    virtual ~BGRMain();

public slots:

    //...
    //...

private:

    //...
    //...
};

#endif // BGRMAIN_H
