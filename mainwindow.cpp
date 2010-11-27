#include <QTextCodec>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMenu>
#include <QErrorMessage>
#include <QSpinBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "antalgorithm.h"
#include "graphscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("cp1251"));

    errMsg = new QErrorMessage(this);
    antAlgorithm = new AntAlgorithm;

    graphScene = new GraphScene(ui->graphicsView->width(), ui->graphicsView->height(), this);
    connect(graphScene, SIGNAL(signalNodesChanged(QList<QVector<float> >)), antAlgorithm, SLOT(setWeightM(QList< QVector<float> >)));
    connect(antAlgorithm, SIGNAL(optimalPathFound(QList<int>)), graphScene, SLOT(drawOptimalPath(QList<int>)));
    connect(antAlgorithm, SIGNAL(strToLog(QString)), this, SLOT(addToLog(QString)));
    connect(antAlgorithm, SIGNAL(showError(QString)), this, SLOT(showError(QString)));
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setScene(graphScene);

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow()
{
    delete antAlgorithm;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::createActions()
{
    //actions painter mode
    actionGroupModes = new QActionGroup(this);
    actionGroupModes->setExclusive(true);

    actionSetModeSelect = new QAction(QIcon(":/images/arrow.png"), tr("Selection mode"), this);
    actionSetModeSelect->setCheckable(true);
    actionGroupModes->addAction(actionSetModeSelect);
    connect(actionSetModeSelect, SIGNAL(toggled(bool)), graphScene, SLOT(setSelectMode()));

    actionSetModeAddPoint = new QAction(QIcon(":/images/round.png"), tr("Add point mode"), this);
    actionSetModeAddPoint->setCheckable(true);
    actionGroupModes->addAction(actionSetModeAddPoint);
    connect(actionSetModeAddPoint, SIGNAL(toggled(bool)), graphScene, SLOT(setAddPoinrMode()));
    actionSetModeAddPoint->setChecked(true);

    actionSetModeAddLine = new QAction(QIcon(":/images/line.png"), tr("Add line mode"), this);
    actionSetModeAddLine->setCheckable(true);
    actionGroupModes->addAction(actionSetModeAddLine);
    connect(actionSetModeAddLine, SIGNAL(toggled(bool)), graphScene, SLOT(setAddLineMode()));

    //actions context point menu
    actionSetPointModeInitial = new QAction(tr("Начальая вершина"), this);
    connect(actionSetPointModeInitial, SIGNAL(triggered()), graphScene, SLOT(setInitialPoint()));

    actionSetPointModeIntermediate = new QAction(tr("Промежуточная вершина"), this);
    connect(actionSetPointModeIntermediate, SIGNAL(triggered()), graphScene, SLOT(setIntermediatePoint()));

    actionSetPointModeFinit = new QAction(tr("Конечная вершина"), this);
    connect(actionSetPointModeFinit, SIGNAL(triggered()), graphScene, SLOT(setFinitPoint()));

    actionRemovePoint = new QAction(QIcon(":/images/minus.png"), tr("Удалить"), this);
    actionRemovePoint->setShortcut(QKeySequence::Delete);
    connect(actionRemovePoint, SIGNAL(triggered()), graphScene, SLOT(deleteSelectedItems()));

    //actions algorithm
    actionRunAlgorithm = new QAction(tr("Запустить"), this);
    connect(actionRunAlgorithm, SIGNAL(triggered()), this, SLOT(runAnts()));
}

void MainWindow::createMenus()
{
    //context point menu
    menuPoint = new QMenu(this);
    menuPoint->addAction(actionSetPointModeInitial);
    menuPoint->addAction(actionSetPointModeIntermediate);
    menuPoint->addAction(actionSetPointModeFinit);
    menuPoint->addSeparator();
    menuPoint->addAction(actionRemovePoint);
    graphScene->setContextMenuForPoint(menuPoint);
}

void MainWindow::createToolBars()
{
    toolBarModes = addToolBar(tr("Graph toolbar"));
    toolBarModes->addActions(actionGroupModes->actions());
    toolBarModes->addSeparator();
    toolBarModes->addAction(actionRemovePoint);

    toolBarAlgorithm = addToolBar(tr("Algorithm tolbar"));
    toolBarAlgorithm->addAction(actionRunAlgorithm);
    spinBox = new QSpinBox(this);
    spinBox->setValue(50);
    spinBox->setMaximum(1000);
    toolBarAlgorithm->addWidget(spinBox);
}

void MainWindow::runAnts()
{
    antAlgorithm->run(graphScene->getInit(), graphScene->getFinit(), spinBox->value());
}

void MainWindow::addToLog(QString str)
{
    ui->textBrowser->append(str);;
}

void MainWindow::showError(QString str)
{
    errMsg->showMessage(str);
}

void MainWindow::on_pushButton_clicked()
{
    antAlgorithm->setParam(ui->doubleSpinBoxAlpha->value(),
                           ui->doubleSpinBoxBeta->value(),
                           ui->doubleSpinBoxVaporizationSpeed->value(),
                           ui->doubleSpinBoxMarkValue->value());
}
