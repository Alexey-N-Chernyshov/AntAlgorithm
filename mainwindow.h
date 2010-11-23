#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphScene;
class QActionGroup;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    GraphScene *graphScene;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    QActionGroup *actionGroupModes;
    QAction *actionSetModeSelect;
    QAction *actionSetModeAddPoint;
    QAction *actionSetModeAddLine;

    QToolBar *toolBarModes;

    void createActions();
    void createToolBars();
};

#endif // MAINWINDOW_H
