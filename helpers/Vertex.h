//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_VERTEX_H
#define SERVER_SIDE_PROJECT_VERTEX_H

enum Color {
    WHITE, GRAY, BLACK
};

template<class T>
class Vertex {
    T *ptr;
    Color color;
public:
    Vertex(T *p) : ptr(p), color(WHITE) {}

    T *getPtr() const {
        return ptr;
    }

    Color getColor() const {
        return color;
    }

    void setPtr(T *ptr) {
        Vertex::ptr = ptr;
    }

    void setColor(Color color) {
        Vertex::color = color;
    }
};

#endif //SERVER_SIDE_PROJECT_VERTEX_H
