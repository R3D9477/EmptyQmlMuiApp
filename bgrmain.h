#ifndef BGRMAIN_H
#define BGRMAIN_H

#include <QObject>

class BGRMain: public QObject
{
    //...
    //...

    Q_OBJECT

public slots:

    //...
    //...

public:

    explicit BGRMain(QObject *parent = nullptr);
    virtual ~BGRMain();

signals:

    //...
    //...

private:

    //...
    //...
};

#endif // BGRMAIN_H
