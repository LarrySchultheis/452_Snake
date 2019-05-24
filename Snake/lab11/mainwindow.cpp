#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snake.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "unistd.h"
#include <iostream>
#include "gameengine.h"
#include <QKeyEvent>

using namespace std;

Snake *sne;
QImage imgscreen;
GameEngine *ge;
//int fruitX, fruitY;
 int lastDir;
 int dir;
//static int score_count = 0;
 bool newGame = false;
 bool pauseFlag = false;
 bool gotUnpaused = false;
 bool justPaused = false;
 int isPaused = 0;
 int difficultyChange;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //s = new Snake();
    imgscreen = QImage (480, 280, QImage::Format_RGB888);
    imgscreen.fill(QColor(Qt::black).rgb());
    difficultyChange = 1;

    //ui->timeDisplay->display(12);


    //fruitX = rand()%45*10;
    //fruitY = rand()%25*10;
/*
    for (int x = 40; x < 60; ++x)
    {
        for (int y = 80; y < 90; ++y)
        {
            imgscreen.setPixel(x,y,qRgb(0, 255, 0));
        }
    }

    for (int x = 40; x < 50; ++x)
    {
        for (int y = 90; y < 100; ++y)
        {
            imgscreen.setPixel(x,y,qRgb(0, 255, 0));
        }
    }

    for (int x = 140; x < 150; ++x)
    {:/path/to/your/image.jpg"
        for (int y = 230; y < 240; ++y)
        {
            imgscreen.setPixel(x,y,qRgb(255, 0, 0));
        }
    }
*/

    lastDir = -1;

    //image = QImage (480, 280, QImage::Format_RGB888);
    QPixmap image("/home/debian/Desktop/GameboyLogo.png");

    ui->timeDisplay->display(10);


    ui->gbaLbl->setPixmap(image);


    ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    ui->pictureLbl->repaint();


    grabKeyboard();

  //  startNewGame();


}

int MainWindow::getDifficulty()
{
    return difficultyChange;
}

void MainWindow::youDied()
{
    QPixmap image("/home/debian/Desktop/youDied.jpg");
    ui->gbaLbl->setPixmap(image);
    ui->gbaLbl->repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    cout << event->key() << endl;
    if (!pauseFlag)
    {
        if (event->key() == 87)
        {
            //w (up)
            moveUp();
        }

        //big ol switch statement
        switch (event->key())
        {
            case 87:
                moveUp();
                break;
            case 65:
                moveLeft();
                break;
            case 83:
                moveDown();
                break;
            case 68:
                moveRight();
                break;
            case 16777234:
                moveLeft();
                break;
            case 16777235:
                moveUp();
                break;
            case 16777236:
                moveRight();
                break;
            case 16777237:
                moveDown();
                break;


            default:
                break;
        }
    }
    switch (event->key())
    {
        case 49:
            difficultyChange = 1;
            break;
        case 50:
            difficultyChange = 2;
            break;
        case 51:
            difficultyChange = 3;
            break;
        case 52:
            difficultyChange = 4;
            break;
        default:
            break;
    }

    if (event->key() == 32)
        pause();
    if (event->key() == 16777216)
        newGame = true;

}


MainWindow getWindow()
{
    //return this;
}

void MainWindow::setSnake(Snake * sn)
{
    sne = sn;
}

void MainWindow::setNewGame (bool b)
{
    newGame = b;
}

bool MainWindow::getNewGame()
{
    return newGame;
}

void MainWindow::setGameEngine (GameEngine * g)
{
    ge = g;
}


/*
int MainWindow::getLastDir()
{
    return lastDir;
}
*/
//void MainWindow::setLastDir(int dir){
  //  lastDir = dir;
//}
/*
Snake* MainWindow::getSnake()
{
    return s;
}

void MainWindow::move(int dir)
{
    //while (1)
    //{
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

    //pthread_exit(NULL);
    //usleep(1000);
    //}
}
*/

bool MainWindow::getPause()
{
    return pauseFlag;
}

void MainWindow::setPause(bool p)
{
    pauseFlag = p;
}

/* Direction Functions Start */
void MainWindow::moveLeft()
{
    //s->setDirection(3);
    if (!pauseFlag)
    {

        if (lastDir == 1)
            return ;
        dir = 3;
        sne->setDirection(dir);
        lastDir = dir;
    }



}



void MainWindow::moveRight()
{
    //s->setDirection(1);
    if (!pauseFlag)
    {

        if (lastDir == 3)
            return ;
        dir = 1;
        sne->setDirection(dir);
        lastDir = dir;
    }





}

void MainWindow::moveUp()
{
    //s->setDirection(0);
    if (!pauseFlag)
    {

        if (lastDir == 2)
            return ;
        dir = 0;
        sne->setDirection(dir);
        lastDir = dir;
    }




}

void MainWindow::updateLevel()
{
    QString out = QString::number(difficultyChange);
    ui->levelDisplay->display(out);
}

void MainWindow::moveDown()
{
    //s->setDirection(2);
    if (!pauseFlag)
    {

        if (lastDir == 0)
            return ;

        dir = 2;
        sne->setDirection(dir);
        lastDir = dir;
    }






}

int MainWindow::getDir()
{
    return dir;
}

/* Direction Functions End */



void MainWindow::tryPause()
{
    pause();
}

void MainWindow::startNewGame()
{

    newGame = true;
    difficultyChange = 0;

}

void MainWindow::setUnpaused(bool up)
{
    gotUnpaused = false;
}

bool MainWindow::getUnpause()
{
    return gotUnpaused;
}

void MainWindow::pause()
{
    //static int pauseval = 0;

    if (isPaused == 1)
    {
        pauseFlag = true;
       // gotUnpaused = false;
        justPaused = true;
        isPaused = 0;
    }
    else
    {
        pauseFlag = false;
        gotUnpaused = true;
       // justPaused = false;
        isPaused = 1;
        //timer_gettime(timerid);
    }
}

bool MainWindow::getJustPaused()
{
    return justPaused;
}

void
MainWindow::setJustPaused(bool fl)
{
    justPaused = fl;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScore(int sc)
{
    QString out = QString::number(sc);
    ui->scoreDisplay->display(sc);
}

void MainWindow::updateTime(int time)
{
    ui->timeDisplay->display(time);
}



void MainWindow::paintSnek()
{
    imgscreen.fill(QColor(Qt::black).rgb());
    //Snake::snek* sn;
    Snake::snek *sn = sne->getStart();
    //cout<<s->getStart()->xCoord << endl;
    //while (1)
   // {
    int i = 0;
    while (sn->nextNode != NULL)
    {
        //int tempX = sn->xCoord;

        //int tempY = sn->yCoord;

    for (int x = sn->xCoord; x < sn->xCoord+10; x++)
    {
        for (int y = sn->yCoord; y < sn->yCoord+10; y++)
        {
            if (sn == sne->getStart())
            {
            imgscreen.setPixel(x, y, qRgb(0, 255, 0));
            }
            else
            {
                imgscreen.setPixel(x, y, qRgb(rand()%255, rand()%255, rand()%255));

            }
            //cout << "x: " << x << " y: " << y << endl;
        }
    }
    sn = sn->nextNode;



    //sleep(1);
    //cout << i << endl;
    i++;

    }

    int fx = ge->getFruitX();
    int fy = ge->getFruitY();
    for (int x = fx; x < fx+10; x++)
    {
        for (int y = fy; y < fy+10; y++)
        {
            imgscreen.setPixel(x, y, qRgb(255, 127, 80));
        }
    }
    //paintFruit();

    ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    ui->pictureLbl->repaint();
    //}
}


void MainWindow::setLastDir(int dir)
{
    lastDir = dir;
}

void MainWindow::setDir(int di)
{
    dir = di;
}

void MainWindow::paintFruit()
{
    int fx = ge->getFruitX();
    int fy = ge->getFruitY();
    for (int x = fx; x < fx+10; x++)
    {
        for (int y = fy; y < fy+10; y++)
        {
            imgscreen.setPixel(x, y, qRgb(255, 127, 80));
        }
    }

    ui->pictureLbl->setPixmap(QPixmap::fromImage(imgscreen));
    ui->pictureLbl->repaint();
}



