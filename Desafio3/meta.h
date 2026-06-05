#ifndef META_H
#define META_H

#include <QGraphicsRectItem>
#include <QObject>

class Meta : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Meta(float x, float y, float ancho, float alto, QObject *parent = nullptr);
};

#endif // META_H
