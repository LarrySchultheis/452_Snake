#ifndef SNAKE_H
#define SNAKE_H


class Snake
{
public:
    typedef struct snek
    {
        snek* nextNode;
        int xCoord, yCoord;
        int color;
    }
    snek;
    Snake();
    void addNewNode();
    snek* getStart();
    void setDirection(int dir);
    void updateSnek(snek *sn);
    void setColor (int c);
    int getDirection();

};

#endif // SNAKE_H
