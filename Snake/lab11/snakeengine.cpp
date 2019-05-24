
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snake.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "unistd.h"
#include "snakeengine.h"
#include <iostream>

using namespace std;




snakeengine::snakeengine()
{
}
void snakeengine::move(int dir)
{
    s->updateSnek(s->getStart());

    paintSnek(s->getStart());
    checkSnakeCollision(s->getStart()->nextNode);
    checkFruit(s->getStart());

    if (dir == 0)
    {
        //up
        boundaryUp(s->getStart());
    }
    else if (dir == 1)
    {
        //right
        boundaryRight(s->getStart());
    }
    else if (dir == 2)
    {
        //down
        boundaryDown(s->getStart());
    }
    else
        boundaryLeft(s->getStart());

    lastDir = s->getDirection();


}

/* Direction Functions Start
void snakeengine::moveLeft()
{
    mw->ui->testOutput->setText("move left");
    s->setDirection(3);
    if (lastDir == 1)
    {
        return;
    }
    //s->updateSnek(s->getStart());

    //paintSnek(s->getStart());
    //checkSnakeCollision(s->getStart()->nextNode);
    //checkFruit(s->getStart());


    //boundaryLeft(s->getStart());
    //move(s->getDirection());

}



void snakeengine::moveRight()
{
    mw->ui->testOutput->setText("move right");
    s->setDirection(1);
    if (lastDir == 3)
        return;
    //s->updateSnek(s->getStart());
    //paintSnek(s->getStart());
    //checkSnakeCollision(s->getStart()->nextNode);
    //checkFruit(s->getStart());

    //boundaryRight(s->getStart());
    //move(s->getDirection());



}

void snakeengine::moveUp()
{
    mw->ui->testOutput->setText("move up");
    s->setDirection(0);
    if (lastDir == 2)
    {
        return;
    }
   // s->updateSnek(s->getStart());
    //paintSnek(s->getStart());
    //checkSnakeCollision(s->getStart()->nextNode);
    //checkFruit(s->getStart());

    //boundaryUp(s->getStart());
    //move(s->getDirection());


}

void snakeengine::moveDown()
{
    mw->ui->testOutput->setText("move down");
    s->setDirection(2);
    if (lastDir == 0)
        return ;
    //s->updateSnek(s->getStart());
    //paintSnek(s->getStart());
    //checkSnakeCollision(s->getStart()->nextNode);
    //checkFruit(s->getStart());

    //boundaryDown(s->getStart());
    //move(s->getDirection());

}

void snakeengine::paintSnek(Snake::snek* sn)
{
    imgscreen.fill(QColor(Qt::black).rgb());

    sn = s->getStart();
    //cout<<s->getStart()->xCoord << endl;

    int i = 0;
    while (sn->nextNode != NULL)
    {
        //int tempX = sn->xCoord;
        //int tempY = sn->yCoord;

    for (int x = sn->xCoord; x < sn->xCoord+10; x++)
    {
        for (int y = sn->yCoord; y < sn->yCoord+10; y++)
        {
            if (sn == s->getStart())
            {
            imgscreen.setPixel(x, y, qRgb(0, 255, 0));
            }
            else
            {
                imgscreen.setPixel(x, y, qRgb(rand()%255, rand()%255, rand()%255));

            }
            cout << "x: " << x << " y: " << y << endl;
        }
    }

    cout << i << endl;
    i++;
    sn = sn->nextNode;

    }
    paintFruit();

    mw->ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    mw->ui->pictureLbl->repaint();
}

void snakeengine::checkSnakeCollision(Snake::snek* sn)
{
    while (sn->nextNode != NULL)
    {
        if (s->getStart()->xCoord == sn->xCoord && s->getStart()->yCoord == sn->yCoord)
        //if (sn->xCoord == sn->nextNode->xCoord && sn->yCoord == sn->nextNode->yCoord)
        {
            mw->ui->testOutput->setText("You Died");
            startNewGame();

        }
        sn = sn->nextNode;
    }
}

void snakeengine::checkFruit(Snake::snek* sn)
{
    if (sn->xCoord == fruitX && sn->yCoord == fruitY)
    {
        //ui->testOutput->setText("got fruit");
        makeFruit();
        s->addNewNode();
        score_count++;
        QString score = QString::number(score_count);
        mw->ui->scoreEdit->setText(QString(score));
    }
}


// Boundary Checking Functions Start
void snakeengine::boundaryUp(Snake::snek* sn)
{
    if(sn->yCoord <= -1)
    {
        startNewGame();
    }
}

void snakeengine::boundaryDown(Snake::snek* sn)
{
    if(sn->yCoord+10 >= 289)
    {
        startNewGame();
    }
}

void snakeengine::boundaryLeft(Snake::snek* sn)
{
    if(sn->xCoord <= -1)
    {
        startNewGame();
    }
}

void snakeengine::boundaryRight(Snake::snek* sn)
{
    if(sn->xCoord+10 >= 489)
    {
        startNewGame();
    }

}
/*Boundary Checking Functions End*/

/* Starts New Game
   Makes a new snek

void snakeengine::startNewGame()
{
    mw->ui->testOutput->setText("new game");
    //imgscreen.fill(QColor(Qt::black).rgb());




    int startDir = rand()%3;
    s = new Snake();
    s->setDirection(startDir);
    s->addNewNode();
    s->addNewNode();
    s->addNewNode();
    score_count = 0;
    QString score = QString::number(score_count);
    mw->ui->scoreEdit->setText(QString(score));




    Snake::snek* sn = s->getStart();

    //cout<<s->getStart()->xCoord << endl;

   // while (sn->nextNode != NULL)
    //{
    /*
    for (int x = sn->xCoord; x < sn->xCoord+10; x++)
    {
        for (int y = sn->yCoord; y < sn->yCoord+10; y++)
        {
            imgscreen.setPixel(x, y, qRgb(0, 255, 0));
            cout << "x: " << x << " y: " << y << endl;
        }
    }
    cout << i << endl;
    i++;
    sn = sn->nextNode;

    }

    // Keep snake from spawning outside boundaries
    Snake::snek* temp = sn;
    while(temp->nextNode != NULL)
    {
        boundaryDown(temp);
        boundaryLeft(temp);
        boundaryRight(temp);
        boundaryUp(temp);

        temp = temp->nextNode;

    }

    makeFruit();
    paintSnek(sn);
    paintFruit();

    mw->ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    mw->ui->pictureLbl->repaint();

//    while (1)
//    {
//        usleep(100);
//        move(s->getDirection());
//    }
}

void snakeengine::makeFruit()
{
    fruitX = rand()%45*10;
    fruitY = rand()%25*10;
}

void snakeengine::paintFruit()
{
    for (int x = fruitX; x < fruitX+10; x++)
    {
        for (int y = fruitY; y < fruitY+10; y++)
        {
            imgscreen.setPixel(x, y, qRgb(255, 127, 80));
        }
    }

    mw->ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    mw->ui->pictureLbl->repaint();
}
*/

