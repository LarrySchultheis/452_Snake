#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snake.h"
#include "gameengine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //int getLastDir();
    //void setLastDir(int dir);
    //void move(int dir);

    //void boundaryUp(Snake::snek* sn);
    //void boundaryDown(Snake::snek* sn);
    //void boundaryLeft(Snake::snek* sn);
    //void boundaryRight(Snake::snek* sn);



     Q_SLOT void paintSnek();

    bool getPause();
    void setPause(bool p);

    //void makeFruit();
     void paintFruit();

    int getDir();
    void setNewGame (bool b);
    void updateScore(int sc);
    int getDifficulty();
    void updateLevel();
    void setLastDir(int dir);
    void setDir(int di);
    bool getNewGame();
    void updateTime(int time);
    //QLCDNumber getDisplay();

    void setJustPaused(bool fl);
    bool getJustPaused();


    void tryPause();

    void youDied();

    void setUnpaused(bool up);
    bool getUnpause();


    void setGameEngine(GameEngine* g);
   // GameEngine* getGameEngine ();

    //void checkFruit(Snake::snek* sn);
    //void checkSnakeCollision(Snake::snek* sn);

    Snake* getSnake();
    void setSnake(Snake * sn);
    MainWindow getWindow();




private slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void startNewGame();
    void pause();






private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
