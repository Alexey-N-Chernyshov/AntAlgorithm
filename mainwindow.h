#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;
class QErrorMessage;
class QSpinBox;
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

public slots:
    void addToLog(QString str);
    void showError(QString str);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    GraphScene *graphScene;
    QErrorMessage *errMsg;

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
    QSpinBox *spinBox;
    QToolBar *toolBarModes;
    QToolBar *toolBarAlgorithm;

    AntAlgorithm *antAlgorithm;

    void createActions();
    void createMenus();
    void createToolBars();

private slots:
    void on_pushButton_clicked();
    void runAnts();
};

#endif // MAINWINDOW_H
