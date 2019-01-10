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
    Position();

    /**
     * Create an x y position object
     * @param xPos x position
     * @param yPos y position
     */
    Position(T xPos, T yPos);

    /**
     * @return x
     */
    T getX() const;

    /**
     * @return y
     */
    T getY() const;

    /**
     * Check if two positions are equal
     * @param other
     * @return
     */
    bool equals(const Position<T> other) const;

    bool operator==(const Position<T> &right) const;

    bool operator<(const Position<T> &right) const;

    template<class V>
    friend ostream &operator<<(ostream &os, Position<V> &position);

    template<class V>
    friend istream &operator>>(istream &os, Position<V> &position);
};


template<class T>
Position<T>::Position() {}

/**
 * Create an x y position object
 * @param xPos x position
 * @param yPos y position
 */
template<class T>
Position<T>::Position(T xPos, T yPos) : x(xPos), y(yPos) {}

/**
 * @return x
 */
template<class T>
T Position<T>::getX() const {
    return x;
}

/**
 * @return y
 */
template<class T>
T Position<T>::getY() const {
    return y;
}

/**
 * Check if two positions are equal
 * @param other
 * @return
 */
template<class T>
bool Position<T>::equals(const Position<T> other) const {
    return other.getX() == this->getX() && other.getY() == this->getY();
}

/**
 * Compares two position objects
 */
template<class T>
bool Position<T>::operator==(const Position<T> &right) const {
    return this->equals(right);
}

/**
 * @return a == b <=> !(a < b) && !(b < a)
 */
template<class T>
bool Position<T>::operator<(const Position<T> &right) const {
    return !(this->getX() == right.getX() && this->getY() == right.getY());
}

/**
 * Writes position to stream
 */
template<class T>
ostream &operator<<(ostream &os, Position<T> &position) {
    os << "(" << position.getX() << "," << position.getY() << ")";
    return os;
}

/**
 * Get position from input stream
 */
template<class T>
istream &operator>>(istream &os, Position<T> &position) {
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

/**
 * Make position hashable
 */
namespace std {
    /**
     * Hash position object
     * @tparam T data type
     */
    template<class T>
    struct hash<Position<T>> {
        std::size_t operator()(const Position<T> &k) const {
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
