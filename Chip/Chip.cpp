#include "stdafx.h"
#include "Chip.h"

Chip::Chip()
    : x_(0)
    , y_(0)
    , color_()
{
    init();
}

Chip::~Chip()
{
}

int Chip::getX() const
{
    return x_;
}

void Chip::setX(int x)
{
    this->x_ = x;
}

int Chip::getY() const
{
    return y_;
}

void Chip::setY(int y)
{
    this->y_ = y;
}

QColor Chip::getColor() const
{
    return color_;
}

void Chip::setColor(QColor color)
{
    this->color_ = color;
}

QRectF Chip::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}

void Chip::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color_.darker(150) : color_;

    if (option->state & QStyle::State_MouseOver)
    {
        fillColor = fillColor.lighter(125);
    }

    const qreal lod = option->levelOfDetailFromTransform(painter->transform());

    if (lod < 0.2)
    {
        if (lod < 0.125)
        {
            painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(13, 13, 97, 57);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;

    if (option->state & QStyle::State_Selected)
    {
        width += 2;
    }

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);

    if (lod >= 1)
    {
        painter->setPen(QPen(Qt::gray, 1));
        painter->drawLine(15, 54, 94, 54);
        painter->drawLine(94, 53, 94, 15);
        painter->setPen(QPen(Qt::black, 0));
    }

    if (lod >= 2)
    {
        QFont font("Times", 10);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->scale(0.1, 0.1);
        painter->drawText(170, 180, QObject::tr("Model: VSC-2000 (Very Small Chip at %1x%2)").arg(x_).arg(y_));
        painter->drawText(170, 200, QObject::tr("Serial number: DLWR-WEER-123L-ZZ33-SDSJ"));
        painter->drawText(170, 220, QObject::tr("Manufacturer: Chip Manufacturer"));
        painter->restore();
    }

    QVarLengthArray<QLineF, 36> lines;

    if (lod >= 0.5)
    {
        for (int i = 0; i <= 10; i += (lod > 0.5 ? 1 : 2))
        {
            lines.append(QLineF(18 + 7 * i, 13, 18 + 7 * i, 5));
            lines.append(QLineF(18 + 7 * i, 54, 18 + 7 * i, 62));
        }

        for (int i = 0; i <= 6; i += (lod > 0.5 ? 1 : 2))
        {
            lines.append(QLineF(5, 18 + i * 5, 13, 18 + i * 5));
            lines.append(QLineF(94, 18 + i * 5, 102, 18 + i * 5));
        }
    }

    if (lod >= 0.4)
    {
        const QLineF lineData[] = 
        {
            QLineF(25, 35, 35, 35)
            , QLineF(35, 30, 35, 40)
            , QLineF(35, 30, 45, 35)
            , QLineF(35, 40, 45, 35)
            , QLineF(45, 30, 45, 40)
            , QLineF(45, 35, 55, 35)
        };

        lines.append(lineData, 6);
    }

    painter->drawLines(lines.data(), lines.size());
}

void Chip::init()
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

