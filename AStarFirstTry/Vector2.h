#pragma once
class Vector2
{
public:
        double x;
        double y;

        Vector2()
        {
            x = -1;
            y = -1;
        }
        Vector2(double xP, double yP) : x(xP), y(yP)
        {

        }
        ~Vector2() {};



        bool operator ==(const Vector2 other)
        {
            if (this->x == other.x && this->y == other.y) return true;
            return false;

        }
        bool operator>(const Vector2& other)
        {
            if (this->x > other.x && this->y > other.y) return true;
            return false;
        }
        bool operator<(const Vector2& other)
        {
            if (this->x < other.x && this->y < other.y) return true;
            return false;
        }

};

