#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;
class AntAlgorithm;
class GraphScene;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    GraphScene *graphScene;

    QActionGroup *actionGroupModes;
    QAction *actionSetModeSelect;
    QAction *actionSetModeAddPoint;
    QAction *actionSetModeAddLine;

    QAction *actionSetPointModeInitial;
    QAction *actionSetPointModeIntermediate;
    QAction *actionSetPointModeFinit;
    QAction *actionRemovePoint;

    QAction *actionRunAlgorithm;

    QMenu *menuPoint;

    QToolBar *toolBarModes;
    QToolBar *toolBarAlgorithm;

    AntAlgorithm *antAlgorithm;

    void createActions();
    void createMenus();
    void createToolBars();

private slots:
    void runAnts();
};

#endif // MAINWINDOW_H
