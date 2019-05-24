#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "snake.h"
#include "mainwindow.h"

using namespace std;

/*typedef struct snek
{
    snek* nextNode;
    int xCoord, yCoord;
    int color;
}
snek;*/

// Collisions
// When snake is out of bounds clear the board

Snake::snek *temp;
Snake::snek* start;
int direction;


//Snake struct
Snake::Snake()
{
    start = new snek();
    start->xCoord = rand()%45*10;
    start->yCoord = rand()%25*10;
    start->nextNode = NULL;
    direction = rand()%3;
    //cout << temp->xCoord << endl;

    temp = start;

}

//Add new node to the snek
void Snake::addNewNode()
{
    snek *sn = new snek();

    // Add node in appropriate spot
    // Up
    if (direction == 0)
    {
        sn->xCoord = temp->xCoord;
        sn->yCoord = temp->yCoord-10;


    }
    // Right
    else if (direction == 1)
    {
        sn->xCoord = temp->xCoord-10;
        sn->yCoord = temp->yCoord;
    }
    // Down
    else if (direction == 2)
    {
        sn->xCoord = temp->xCoord;
        sn->yCoord = temp->yCoord+10;
    }
    // Left
    else
    {
        sn->xCoord = temp->xCoord+10;
        sn->yCoord = temp->yCoord;
    }
    //temp->xCoord = rand();
    //cout << temp->xCoord << endl;

    //Set the new current node to current.next
    temp->nextNode = sn;

    //set last node.next = NULL
    sn->nextNode = NULL;
    temp = sn;
}

Snake::snek* Snake::getStart()
{
    return start;
}

void Snake::setDirection(int dir){
    direction = dir;
}

//update snake coords (set all nodes to follow head)
void Snake::updateSnek(Snake::snek* sn)
{
    //Snake::snek* sn = start;
    int tempX = sn->xCoord;
    int tempY = sn->yCoord;

    if (direction == 0)
    {
        sn->xCoord = sn->xCoord;
        sn->yCoord = sn->yCoord-10;

    }

    else if (direction == 1)
    {
        sn->xCoord = sn->xCoord+10;
        sn->yCoord = sn->yCoord;
    }

    else if (direction == 2)
    {
        sn->xCoord = sn->xCoord;
        sn->yCoord = sn->yCoord+10;
    }
    else
    {
        sn->xCoord = sn->xCoord-10;
        sn->yCoord = sn->yCoord;
    }
    sn = sn->nextNode;

    while (sn->nextNode != NULL)
    {
        int tX2 = sn->xCoord;
        int tY2 = sn->yCoord;

        sn->xCoord = tempX;
        sn->yCoord = tempY;

        tempX = tX2;
        tempY = tY2;

        sn = sn->nextNode;
    }
}

void Snake::setColor(int c)
{
    //color = c;
}

int Snake::getDirection()
{
    return direction;
}


