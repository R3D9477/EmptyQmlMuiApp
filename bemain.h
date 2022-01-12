#ifndef BEMAIN_H
#define BEMAIN_H

#include <QObject>

class BEMain: public QObject
{
    //...
    //...

    Q_OBJECT

signals:

    //...
    //...

public:

    explicit BEMain(QObject *parent = nullptr);
    virtual ~BEMain();

public slots:

    //...
    //...

private:

    //...
    //...
};

#endif // BEMAIN_H
