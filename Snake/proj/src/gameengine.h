#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//#include "mainwindow.h"
#include "snake.h"

class GameEngine
{
public:
    GameEngine();
    GameEngine(void* w);
    //void *updateSnek();
    void check();
    void checkSnakeCollisions(Snake::snek* sn);
    void checkFruit();
    void checkBoundaries(Snake::snek*sn);

    int getLastDir();
    void setLastDir(int dir);
    void setDifficulty(int d);
    void move(int dir);

    void startNewGame();

    bool getDead();

    void boundaryUp(Snake::snek* sn);
    void boundaryDown(Snake::snek* sn);
    void boundaryLeft(Snake::snek* sn);
    void boundaryRight(Snake::snek* sn);

    void makeFruit();
    //void time();
    //void setWindow(MainWindow* m);

    bool getPaintFlag();
    void setPaintFlag(bool p);

    void setDead(bool fl);

    bool getThatFruitFlag();
    void setThatFruitFlag(bool fl);

    int getScore();

    int getFruitX();
    int getFruitY();

    Snake* getSnake();



};

#endif // GAMEENGINE_H
