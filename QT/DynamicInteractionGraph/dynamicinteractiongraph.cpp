#include "dynamicinteractiongraph.h"
#include "ui_dynamicinteractiongraph.h"

#include <QTimer>

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
    if (!tmp.circCollide(nodes))
        nodes.append(tmp);
}

void DynamicInteractionGraph::addArc(const node &start, const node &end) {
    if (start != end) {
        arc tmp(start, end);
        if (!arcs.contains(tmp))
            arcs.append(tmp);
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
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> gen_distr(0, MAX_PER_INTERACTION); // define the range
    std::uniform_int_distribution<> x_distr(0, 1000);
    std::uniform_int_distribution<> y_distr(0, 500);

    int times = gen_distr(gen);
    for (int i = 0; i < times; ++i) {
        if (nodes.size() <= 30) {
            int x = x_distr(gen);
            int y = y_distr(gen);
            addNode(x, y);
        }
    }

    std::uniform_int_distribution<> node_index_distr(0, nodes.size()-1);
    times = gen_distr(gen);
    for (int i = 0; i < times; ++i) {
        addArc(nodes.at(node_index_distr(gen)), nodes.at(node_index_distr(gen)));
    }
    std::uniform_int_distribution<> arc_index_distr(0, arcs.size()-1);
    times = gen_distr(gen);
    for (int i = 0; i < times; ++i) {
        arc a = arcs.at(arc_index_distr(gen));
        a.increaseInteraction();
    }
    drawArcs();
    drawNodes();

}

DynamicInteractionGraph::~DynamicInteractionGraph()
{
    delete ui;
}

