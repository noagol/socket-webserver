//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_POSITION_H
#define SERVER_SIDE_PROJECT_POSITION_H

template<class T>
class Position {
    T x;
    T y;
public:
    Position(){}

    Position(T xPos, T yPos) : x(xPos), y(yPos) {}

    T getX() const {
        return x;
    }

    T getY() const {
        return y;
    }

    bool equals(Position<T> other) {
        return other.getX() == this->getX() && other.getY() == this->getY();
    }
};

#endif //SERVER_SIDE_PROJECT_POSITION_H
