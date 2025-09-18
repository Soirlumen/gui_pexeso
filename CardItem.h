#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class CardItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    CardItem(int idx, QGraphicsItem *parent = nullptr)
        : QObject(), QGraphicsRectItem(parent), index(idx) {}

    int index;

signals:
    void clicked(int idx);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        emit clicked(index);
        QGraphicsRectItem::mousePressEvent(event);
    }
};

#endif // CARDITEM_H
