#ifndef POSITION_HPP
#define POSITION_HPP

class Position
{
private:
    int _x;
    int _y;

public:
    Position(int x, int y);
    Position(Position &p);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    double dist(const Position &pos);
    Position &operator=(const Position &p);
    bool operator==(const Position &p);
};
#endif