#ifndef TRI_MESH_FACE_H
#define TRI_MESH_FACE_H

#include <cassert>

class Triangle {
  public:
    unsigned int vertices[3];

    inline unsigned int& operator[](unsigned int index) {
        assert(index < 3);
        return vertices[index];
    }
};

#endif
