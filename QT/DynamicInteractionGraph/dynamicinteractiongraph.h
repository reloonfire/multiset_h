#ifndef DYNAMICINTERACTIONGRAPH_H
#define DYNAMICINTERACTIONGRAPH_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <stdlib.h>
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

        QColor colorize(unsigned int ratio) {
            // ration è un numero tra 0.0 e 1.0, quindi va sempre diviso per un determinato range
            //we want to normalize ratio so that it fits in to 6 regions
            //where each region is 256 units long
            // https://stackoverflow.com/questions/40629345/fill-array-dynamicly-with-gradient-color-c
            int normalized = int(ratio * 256 * 6);

            //find the region for this position
            int region = normalized / 256;

            //find the distance to the start of the closest region
            int x = normalized % 256;

            uint8_t r = 0, g = 0, b = 0;
            switch (region)
            {
            case 0: r = 255; g = 0;   b = 0;   g += x; break;
            case 1: r = 255; g = 255; b = 0;   r -= x; break;
            case 2: r = 0;   g = 255; b = 0;   b += x; break;
            case 3: r = 0;   g = 255; b = 255; g -= x; break;
            case 4: r = 0;   g = 0;   b = 255; r += x; break;
            case 5: r = 255; g = 0;   b = 255; b -= x; break;
            }

            return QColor(r, g, b);
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
            interaction = interaction + 1;
            // devo cambiare i colori dei nodi collegati a questo arco
            start.changeColor(interaction);
            end.changeColor(interaction);
            // Cambio testo
            tag->setPlainText(QString("%1").arg(interaction));
        }
    };

    void addNode(int posX, int posY);

    void addArc(const node &start, const node &end);

    void drawNodes();

    void drawArcs();

    Ui::DynamicInteractionGraph *ui;
    QGraphicsScene *scene;
    QVector<node> nodes;
    QVector<arc> arcs;
public slots:
    void step();

};
#endif // DYNAMICINTERACTIONGRAPH_H
