#include "mainwindow.h"
#include <QApplication>
#include <ctime>
#include <iostream>
#include <QThread>
#include <thread>
#include "unistd.h"
#include "gameengine.h"
#include <QMetaObject>


#include <stdio.h>  /* for puts() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for sleep() */
#include <stdlib.h> /* for EXIT_SUCCESS */

#include <signal.h> /* for `struct sigevent` and SIGEV_THREAD */
#include <time.h>   /* for timer_create(), `struct itimerspec`,
                     * timer_t and CLOCK_REALTIME
                     */
//#include <sys/time.h>

using namespace std;

char info[] = "5 seconds elapsed.";
timer_t timerid;
struct sigevent sev;
struct itimerspec trigger;
int currentTime = 10;
int pauseTime = 10;
bool pFlag;

typedef struct moveArgs
{
    GameEngine *ge;
    MainWindow *w;
    //int dir;
} moveArgs;

Snake *sn;
MainWindow* win;
GameEngine* gePtr;
moveArgs* margs;


//handles signals from the timer
void thread_handler(union sigval sv) {
        char *s = (char*) sv.sival_ptr;
        //int pausetime = 10;

        /* Will print "5 seconds elapsed." */
        //puts(s);

        //if not paused create new fruit
        if (!win->getPause())
        {
            if (currentTime == 0)
            {
                gePtr->makeFruit();
                currentTime = 10;
            }
            currentTime--;
        }



       // timer_delete(timerid);

        memset(&sev, 0, sizeof(struct sigevent));
        memset(&trigger, 0, sizeof(struct itimerspec));



        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = &thread_handler;
        sev.sigev_value.sival_ptr = &info;



        timer_create(CLOCK_REALTIME, &sev, &timerid);



        trigger.it_value.tv_sec = 1;

        timer_settime(timerid, 0, &trigger, NULL);

}



//function for updating the snek;
void *moveSnek (void* args)
{

    MainWindow* w = margs->w;//(MainWindow *)args.w;
    GameEngine* ge = margs->ge;//(GameEngine*) args.ge;

    //main thread loop
    while (1)
    {
        if (w->getNewGame())
        {
            ge->startNewGame();
            w->setDir(rand()%3);
            w->setLastDir(rand()%3);

            w->setNewGame(false);
        }
        if (!w->getPause())
        {
            ge->move(sn->getDirection());
        }


        //set snake speed based on difficulty
        if (w->getDifficulty() == 1)
        {
            usleep(100000);
        }
        else if (w->getDifficulty() == 2)
        {
            usleep(50000);
        }
        else if (w->getDifficulty() == 3)
            usleep(40000);
        else
            usleep(32000);
    }
}

//function for updating the gui
void *paintSnek (void* w)
{
    while (1)
    {
        //if game was just unpaused
        //this is put here because it is the most frequently updated thread



        //win->updateTime(timer_gettime(timerid, &trigger));

        //if that fruit was just grabbed
        //reset that timer


        //timer_gettime(timerid, &trigger);

        QMetaObject::invokeMethod(win, "paintSnek");

        if (gePtr->getThatFruitFlag())
        {
            currentTime = 10;
            gePtr->setThatFruitFlag(false);
        }

        if (gePtr->getDead())
        {
            currentTime = 10;
            gePtr->setDead(false);
        }

        win->updateScore(gePtr->getScore());
        win->updateLevel();
        win->updateTime(currentTime);



        usleep(30000);
    }
}



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    win = &w;
    GameEngine *ge = new GameEngine();
    gePtr = ge;

    ge->startNewGame();
    //win->tryPause();
    sn = ge->getSnake();
    w.setSnake(sn);

    w.setGameEngine(ge);

    moveArgs ma;
    ma.ge = ge;
    ma.w = win;

    margs = &ma;



    char info[] = "5 seconds elapsed.";
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec trigger;

    // Set all `sev` and `trigger` memory to 0
    memset(&sev, 0, sizeof(struct sigevent));
    memset(&trigger, 0, sizeof(struct itimerspec));



    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &thread_handler;
    sev.sigev_value.sival_ptr = &info;



    timer_create(CLOCK_REALTIME, &sev, &timerid);


    trigger.it_value.tv_sec = 1;


    timer_settime(timerid, 0, &trigger, NULL);






    pthread_t paintTh, moveTh;

    pthread_create(&moveTh, NULL, moveSnek, (void*) margs);
    pthread_create(&paintTh, NULL, paintSnek, (void*) win);


    w.show();
    return a.exec();

}







