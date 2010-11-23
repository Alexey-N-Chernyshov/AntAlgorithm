#include <QTextCodec>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("cp1251"));
    graphScene = new GraphScene(ui->graphicsView->width(), ui->graphicsView->height(), this);
    ui->graphicsView->setScene(graphScene);

    createActions();
    createToolBars();
}

MainWindow::~MainWindow()
{
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
}

void MainWindow::createToolBars()
{
    toolBarModes = new QToolBar(tr("Graph toolbar"), this);
    toolBarModes->addActions(actionGroupModes->actions());
}
