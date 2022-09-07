#ifndef DYNAMICINTERACTIONGRAPH_H
#define DYNAMICINTERACTIONGRAPH_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <random>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class DynamicInteractionGraph; }
QT_END_NAMESPACE

class DynamicInteractionGraph : public QMainWindow
{
    Q_OBJECT

public:
    DynamicInteractionGraph(QWidget *parent = nullptr);
    ~DynamicInteractionGraph();

private:

    struct node {
        qreal xPos;
        qreal yPos;

        unsigned int interactionLevel = 0;
        unsigned int diameter = 20;
        QGraphicsEllipseItem *ellipse;

        node(qreal xPos, qreal yPos) : xPos(xPos), yPos(yPos) {
            QBrush greenBrush(colorize((this->interactionLevel)/20));
            QPen blackPen(Qt::black);
            blackPen.setWidth(3);

            ellipse = new QGraphicsEllipseItem(xPos, yPos, diameter, diameter, nullptr);
            ellipse->setBrush(greenBrush);
            ellipse->setPen(blackPen);
        }

        void changeColor(unsigned int interactionLevel) {
            if (this->interactionLevel < interactionLevel) {
                this->interactionLevel = interactionLevel;
                // Cambio colore seguendo la palette
                this->ellipse->setBrush(QBrush(colorize((this->interactionLevel)/5)));
            }
        }

        QColor colorize(int v) {
            qreal rv = qreal(v) / 6;
            QColor c = QColor::fromHsl(205 - (205 - 42) * rv, 200, 135);
            return c;
        }

        inline bool circCollide(QList<node> nodes) {
            QPointF c1 = this->ellipse->boundingRect().center();
            foreach (node t, nodes) {
                qreal distance = QLineF(c1, t.ellipse->boundingRect().center()).length();
                if ( distance <= 100 ) return true;
            }
            return false;
        }

        bool operator==(const node &other) const {
            return (this->xPos == other.xPos && this->yPos == other.yPos);
        }

        bool operator!=(const node &other) const {
            return !(*this == other);
        }
    };

    struct arc {
        unsigned int interaction;
        node start;
        node end;
        QGraphicsLineItem * line;
        QGraphicsTextItem * tag;

        arc(const node &start, const node &end) : interaction(1), start(start), end(end) {
            QPen blackPen(Qt::black);
            blackPen.setWidth(2);

            QPoint pnt1((start.xPos+(start.diameter/2)), (start.yPos+(start.diameter/2)));
            QPoint pnt2((end.xPos+(end.diameter/2)), (end.yPos+(end.diameter/2)));

            line = new QGraphicsLineItem(pnt1.x(), pnt1.y(), pnt2.x(), pnt2.y());
            line->setPen(blackPen);

            tag = new QGraphicsTextItem(line);
            tag->setPlainText(QString("%1").arg(interaction));
            tag->setPos(centerText());
        }

        QPoint centerText() {
            //qreal c_ang_perp = 1 - ((start.yPos - end.yPos) / (start.xPos - end.xPos));
            QPoint pnt1(((start.xPos+end.xPos)/2), ((start.yPos+end.yPos)/2));

            return pnt1;
        }

        void increaseInteraction() {
            this->interaction++;
            // devo cambiare i colori dei nodi collegati a questo arco
            start.changeColor(interaction);
            end.changeColor(interaction);
            // Cambio testo
            tag->setPlainText(QString("%1").arg(interaction));
        }

        bool operator==(const arc &other) const {
            return (this->start == other.start && this->end == other.end);
        }
    };

    void addNode(int posX, int posY);

    void addArc(const node &start, const node &end);

    void drawNodes();

    void drawArcs();

    Ui::DynamicInteractionGraph *ui;
    QGraphicsScene *scene;
    QGraphicsItemGroup *nodesGroup;
    QGraphicsItemGroup *arcsGroup;
    QList<node> nodes;
    QList<arc> arcs;
public slots:
    void step();

};

#endif // DYNAMICINTERACTIONGRAPH_H
