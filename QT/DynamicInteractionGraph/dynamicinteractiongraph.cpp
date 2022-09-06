#include "dynamicinteractiongraph.h"
#include "ui_dynamicinteractiongraph.h"

#include <QTimer>

DynamicInteractionGraph::DynamicInteractionGraph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynamicInteractionGraph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    addNode(0, 0);
    addNode(0, 200);
    addArc(nodes.at(0), nodes.at(1));
    drawArcs();
    drawNodes();
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(step()));
    t->start(1000);
}

void DynamicInteractionGraph::addNode(int xPos, int yPos) {
    node tmp(xPos, yPos);
    nodes.append(tmp);
}

void DynamicInteractionGraph::addArc(const node &start, const node &end) {
    arc tmp(start, end);
    arcs.append(tmp);
}

void DynamicInteractionGraph::drawNodes() {
    for(node n : nodes) {
       scene->addItem(n.ellipse);
    }
}

void DynamicInteractionGraph::drawArcs() {
    for (arc a : arcs) {
        scene->addItem(a.line);
        scene->addItem(a.tag);
    }
}

void DynamicInteractionGraph::step() {
    for (arc a : arcs) {
        a.increaseInteraction();
    }
}

DynamicInteractionGraph::~DynamicInteractionGraph()
{
    delete ui;
}

