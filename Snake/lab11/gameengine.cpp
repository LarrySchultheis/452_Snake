#include "gameengine.h"
#include "snake.h"
#include "mainwindow.h"
#include "unistd.h"
#include <iostream>

Snake* s;
MainWindow* mw;
bool gameOn, paint;
bool dead;
int fruitX, fruitY;
//int lastDir;
int curTime;
int score;
int difficulty;
bool gotThatFruit;

using namespace std;

GameEngine::GameEngine()
{
    gameOn = false;
    paint = false;
    curTime = 0;
    score = 0;
    difficulty = 1;
}

GameEngine::GameEngine(void *w)
{
    gameOn = false;
    paint = false;
    curTime = 0;
    score = 0;
    difficulty = 1;
    mw = (MainWindow*)w;
}



//void *updateSnek()
//{

//}

//void GameEngine::setWindow(MainWindow *m)
//{
  //  mw = m;
//}

void GameEngine::startNewGame()
{
    int startDir = rand()%3;
    //pause();
    score = 0;
    s = new Snake();
    s->setDirection(startDir);
    s->addNewNode();
    s->addNewNode();
    s->addNewNode();
    //score_count = 0;
    //QString score = QString::number(score_count);
    //ui->scoreEdit->setText(QString(score));

    // Keep snake from spawning outside boundaries
    Snake::snek* temp = s->getStart();
    while(temp->nextNode != NULL)
    {
        boundaryDown(temp);
        boundaryLeft(temp);
        boundaryRight(temp);
        boundaryUp(temp);

        temp = temp->nextNode;

    }
    makeFruit();
   // mw->paintFruit(fruitX, fruitY);


    paint = true;

    gameOn = false;
   // mw->tryPause();
    //dead = false;


    //win.paintSnek(s);
    //win.paintFruit(fruitX, fruitY);

}

void GameEngine::setDead(bool fl)
{
    dead = fl;
}

void GameEngine::setThatFruitFlag(bool fl)
{
    gotThatFruit = fl;
}

bool GameEngine::getThatFruitFlag()
{
    return gotThatFruit;
}

bool GameEngine::getDead()
{
    return dead;
}

int GameEngine::getScore()
{
    return score;
}

void GameEngine::setDifficulty(int d)
{
    difficulty = d;
}


void GameEngine::boundaryUp(Snake::snek* sn)
{
    if(sn->yCoord <= -1)
    {
        dead = true;
        startNewGame();
    }
}

void GameEngine::boundaryDown(Snake::snek* sn)
{
    if(sn->yCoord+10 >= 289)
    {
        dead = true;
        startNewGame();
    }
}

void GameEngine::boundaryLeft(Snake::snek* sn)
{
    if(sn->xCoord <= -1)
    {
        dead = true;
        startNewGame();
    }
}

void GameEngine::boundaryRight(Snake::snek* sn)
{
    if(sn->xCoord+10 >= 489)
    {
        dead = true;
        startNewGame();
    }
}

void GameEngine::checkSnakeCollisions(Snake::snek* sn)
{
    while (sn->nextNode != NULL)
    {
        if (s->getStart()->xCoord == sn->xCoord && s->getStart()->yCoord == sn->yCoord)
        //if (sn->xCoord == sn->nextNode->xCoord && sn->yCoord == sn->nextNode->yCoord)
        {
            startNewGame();

               dead = true;
        }
        sn = sn->nextNode;
    }
}

void GameEngine::checkFruit()
{
    Snake::snek *sn = s->getStart();
    if (sn->xCoord == fruitX && sn->yCoord == fruitY)
    {
        //ui->testOutput->setText("got fruit");
        makeFruit();
        s->addNewNode();
        gotThatFruit = true;
        curTime = 0;
        if (mw->getDifficulty() == 1)
            score++;
        else if (mw->getDifficulty() == 2)
            score += 2;
        else if (mw->getDifficulty() == 3)
            score += 4;
        else
            score += 6;
        //score_count++;
        //QString score = QString::number(score_count);
        //ui->scoreEdit->setText(QString(score));
    }
}


void GameEngine::checkBoundaries(Snake::snek* sn)
{
    boundaryUp(sn);
    boundaryRight(sn);
    boundaryLeft(sn);
    boundaryDown(sn);
}

void GameEngine::check ()
{
    Snake::snek* temp = s->getStart();
   // while (temp->nextNode != NULL)
   // {
        checkBoundaries(temp);
   // }

    checkSnakeCollisions(s->getStart()->nextNode);


    checkFruit();
}

void GameEngine::move(int dir)
{
   // while (1)
   // {
    s->updateSnek(s->getStart());

    check();
    //checkFruit();
    //checkSnakeCollisions(s->getStart()->nextNode);

    s->setDirection(dir);

    //paintSnek(s->getStart());
    //checkSnakeCollision(s->getStart()->nextNode);
    //checkFruit(s->getStart());

    if (s->getDirection() == 0)
    {
        //up
        //boundaryUp(s->getStart());
    }
    else if (s->getDirection() == 1)
    {
        //right
        //boundaryRight(s->getStart());
    }
    else if (s->getDirection() == 2)
    {
        //down
        //boundaryDown(s->getStart());
    }
    //else
        //boundaryLeft(s->getStart());
    //cout << "moved" << endl;

    //lastDir = s->getDirection();
    //cout << "moved" << endl;


    //usleep(500);
    //}

}

void GameEngine::makeFruit()
{
    fruitX = rand()%45*10;
    fruitY = rand()%25*10;
}

int GameEngine::getFruitX()
{
    return fruitX;
}
int GameEngine::getFruitY()
{
    return fruitY;
}

bool GameEngine::getPaintFlag()
{
    return paint;
}

void GameEngine::setPaintFlag(bool p)
{
    paint = p;
}

Snake* GameEngine::getSnake()
{
    return s;
}



