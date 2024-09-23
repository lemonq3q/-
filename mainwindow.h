#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"
#include <QWidget>

class QFrame;
class QPushButton;
class QTextEdit;
class ChessScene;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateText();

private:
    QFrame *left;
    QPushButton *start;
    QPushButton *suggest;
    QPushButton *autoplay;
    QTextEdit *display;
    QGraphicsView *chessboard;
    ChessScene *chessScene;
};
#endif // MAINWINDOW_H
