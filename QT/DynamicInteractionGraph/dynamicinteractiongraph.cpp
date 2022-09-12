#include "dynamicinteractiongraph.h"
#include "ui_dynamicinteractiongraph.h"

#include <QTimer>
#include <QDebug>

#define MAX_PER_INTERACTION 5

DynamicInteractionGraph::DynamicInteractionGraph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynamicInteractionGraph)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    setCentralWidget(ui->graphicsView);
    nodesGroup = new QGraphicsItemGroup();
    arcsGroup = new QGraphicsItemGroup();
    scene->addItem(arcsGroup);
    scene->addItem(nodesGroup);
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(step()));
    t->start(1000);
}

void DynamicInteractionGraph::addNode(int xPos, int yPos) {
    node tmp(xPos, yPos);
    if (!tmp.circCollide(nodes) && !nodes.contains(tmp))
        nodes.push_back(tmp);
}

void DynamicInteractionGraph::addArc(const node &start, const node &end) {
    if (start != end) {
        arc tmp(start, end);
        if (!arcs.contains(tmp)) {
            arcs.push_back(tmp);
            qDebug() << "Adding arc to vector";
        }
    }
}

void DynamicInteractionGraph::drawNodes() {
    for(node n : nodes) {
        nodesGroup->addToGroup(n.ellipse);
    }
}

void DynamicInteractionGraph::drawArcs() {
    for (arc a : arcs) {
        arcsGroup->addToGroup(a.line);
        arcsGroup->addToGroup(a.tag);
    }
}

void DynamicInteractionGraph::step() {
    // SETUP RNG
    std::random_device rd; // obtain a random number from hardware
    srand(rd());

    int times = rand() % 5;
    for (int i = 0; i < times; ++i) {
        if (nodes.size() <= 30) {
            int x = rand() % ui->graphicsView->width();
            int y = rand() % ui->graphicsView->height();
            addNode(x, y);
        }
    }

    times = rand() % 5;
    for (int i = 0; i < times; ++i) {
        addArc(nodes.at(rand() % nodes.size()), nodes.at(rand() % nodes.size()));
    }
    if (!arcs.empty()) {
        times = rand() % 5;
        for (int i = 0; i < times; ++i) {
            arc  * a = &arcs[rand() % arcs.size()];
            a->increaseInteraction();
        }
    }
    drawArcs();
    drawNodes();

}

DynamicInteractionGraph::~DynamicInteractionGraph()
{
    QList<QGraphicsItem*> all = scene->items();
    for (int i = 0; i < all.size(); i++)
    {
        QGraphicsItem *gi = all[i];
        if(gi->parentItem()==NULL) {
            delete gi;
        }
    }
    delete ui;
}

