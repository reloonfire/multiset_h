#ifndef DYNAMICINTERACTIONGRAPH_H
#define DYNAMICINTERACTIONGRAPH_H

#include <QMainWindow>
#include <cstdlib>
#include <random>
#include <QVector>
#include <QPoint>
#include <QLabel>

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
        QPoint p;

        unsigned int interactionLevel = 0;
        unsigned int diameter = 20;

        node(qreal xPos, qreal yPos) : p(xPos, yPos) {
        }

        QColor colorize() {
            qreal rv = qreal(interactionLevel) / 8;
            if (rv >= 1) rv = 1;
            QColor c = QColor::fromHsl(205 - (205 - 42) * rv, 200, 135);
            return c;
        }

        bool isValid(QVector<node> nodes) const {
            for (node n : nodes) {
                if (qAbs(p.x() - n.p.x()) + qAbs(p.y() - n.p.y()) < 50)
                    return false;
            }
            return true;
        }

        bool operator==(const node &other) const {
            return (this->p == other.p);
        }

        bool operator!=(const node &other) const {
            return !(*this == other);
        }
    };

    struct arc {
        unsigned int interaction;
        unsigned int startNodeIndex;
        unsigned int endNodeIndex;

        arc(unsigned int start, unsigned int end) : interaction(1), startNodeIndex(start), endNodeIndex(end) {
        }

        bool operator==(const arc &other) const {
            return (this->startNodeIndex == other.startNodeIndex && this->endNodeIndex == other.endNodeIndex) || (this->startNodeIndex == other.endNodeIndex && this->endNodeIndex == other.startNodeIndex);
        }
    };

    void addNode(int posX, int posY);

    void addArc(int startIndex, int endIndex);

    void draw(QPainter &painter);

    void increaseInteraction(unsigned int arcIndex);

    Ui::DynamicInteractionGraph *ui;
    QLabel *canvas;
    QVector<node> nodes;
    QVector<arc> arcs;
public slots:
    void step();

};

#endif // DYNAMICINTERACTIONGRAPH_H
