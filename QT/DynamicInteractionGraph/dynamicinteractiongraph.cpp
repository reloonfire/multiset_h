#include "dynamicinteractiongraph.h"
#include "qpainter.h"
#include "ui_dynamicinteractiongraph.h"

#include <QTimer>
#include <QDebug>

#define MAX_PER_INTERACTION 5

DynamicInteractionGraph::DynamicInteractionGraph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynamicInteractionGraph)
{
    ui->setupUi(this);
    canvas = new QLabel();
    canvas->setMargin(10);
    canvas->setScaledContents(true);
    setCentralWidget(canvas);

    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(step()));
    t->start(1000);
}

void DynamicInteractionGraph::addNode(int xPos, int yPos) {
    node tmp(xPos, yPos);
    if (tmp.isValid(nodes))
        nodes.push_back(tmp);
}

void DynamicInteractionGraph::addArc(int startIndex, int endIndex) {
    if (startIndex != endIndex) {
        arc tmp(startIndex, endIndex);
        if (!arcs.contains(tmp)) {
            arcs.push_back(tmp);

        }
    }
}

void DynamicInteractionGraph::increaseInteraction(unsigned int arcIndex) {
    arc &a = arcs[arcIndex];
    ++(a.interaction);
    if (nodes[a.startNodeIndex].interactionLevel < a.interaction)
        nodes[a.startNodeIndex].interactionLevel = a.interaction;
    if (nodes[a.endNodeIndex].interactionLevel < a.interaction)
        nodes[a.endNodeIndex].interactionLevel = a.interaction;
}

void DynamicInteractionGraph::step() {
    QPainter painter;
    QPicture picture;
    // SETUP RNG
    std::random_device rd; // obtain a random number from hardware
    srand(rd());

    int times = rand() % 5;
    for (int i = 0; i < times; ++i)
    {
        if (nodes.size() <= 30)
        {
            int x = rand() % 500;
            int y = rand() % 500;
            addNode(x, y);
        }
    }
    if (!nodes.empty())
    {
        times = rand() % 5;
        for (int i = 0; i < times; ++i)
        {
            addArc(rand() % nodes.size(), rand() % nodes.size());
        }
    }

    if (!arcs.empty())
    {
        times = rand() % 5;
        for (int i = 0; i < times; ++i)
        {
            increaseInteraction(rand() % arcs.size());
        }
    }

    painter.begin(&picture);
    painter.setPen("transparent");
    painter.drawPoint(0,0);
    painter.drawPoint(500, 500);
    draw(painter);
    canvas->setPicture(picture);
    painter.end();
}

void DynamicInteractionGraph::draw(QPainter &painter) {

    painter.setPen(Qt::black);
    painter.setBrush(Qt::cyan);
    // paint all points in the vector

    for (int i = 0; i < arcs.size(); i++) {
        painter.setPen(Qt::black);
        node n1 = nodes[arcs[i].startNodeIndex];
        node n2 = nodes[arcs[i].endNodeIndex];
        painter.drawLine(n1.p, n2.p);
        // draw the interactions number at the center of the arch, if it changes delete old one
        painter.drawText((n1.p.x() + n2.p.x())/2, (n1.p.y() + n2.p.y())/2, QString::number(arcs[i].interaction));
    }

    for (int i = 0; i < nodes.size(); i++) {
        painter.setBrush(QBrush(nodes[i].colorize()));
        painter.drawEllipse(nodes[i].p, 10, 10);
    }

}

DynamicInteractionGraph::~DynamicInteractionGraph() {
    delete ui;
}

