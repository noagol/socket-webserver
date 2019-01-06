//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_POSITION_H
#define SERVER_SIDE_PROJECT_POSITION_H

#include "ostream"
#include "StringHelpers.h"

using namespace std;

template<class T>
class Position {
    T x;
    T y;
public:
    Position() {}

    Position(T xPos, T yPos) : x(xPos), y(yPos) {}

    T getX() const {
        return x;
    }

    T getY() const {
        return y;
    }

    bool equals(const Position<T> other) const {
        return other.getX() == this->getX() && other.getY() == this->getY();
    }

    bool operator==(const Position<T> &right) const{
        return this->equals(right);
    }

    bool operator<(const Position<T> &right) const {
        return !(this->getX() == right.getX() && this->getY() == right.getY());
    }

    friend ostream &operator<<(ostream &os, Position &position) {
        os << "(" << position.getX() << "," << position.getY() << ")";
        return os;
    }

    friend istream &operator>>(istream &os, Position &position) {
        string input;
        os >> input;

        // Split
        vector<string> spl = split(&input, ',');

        // Turn to streams
        istringstream x{spl.at(0).substr(1)};
        istringstream y{spl.at(1).substr(0, spl.at(0).size() - 1)};

        // Write to object
        x >> position.x;
        y >> position.y;

        return os;
    }
};

namespace std {

    template <class T>
    struct hash<Position<T>>
    {
        std::size_t operator()(const Position<T>& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<int>()(k.getX()) << 1)) >> 1
                   ^ (hash<int>()(k.getY()) << 1);
        }
    };

}

#endif //SERVER_SIDE_PROJECT_POSITION_H
