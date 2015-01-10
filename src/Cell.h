#ifndef CELL_H
#define CELL_H

#include <vector>

#include "Triangle.h"
#include "Vector.h"

extern double CELL_SIZE;

class Cell {

  private:
    unsigned char   cellCase;
    long            cellX, cellY, cellZ;
    bool            render;
    double          density[8];

    void            CalculateCase();
    double          GetDensity(double, double, double);
    double          GetDensity(Vector);
    int             SetupPolygons();

    std::vector<Triangle>   triangles;
    std::vector<Vector>     vertices;

  public:
    static Vector   corners[8];
    static void  init();
                 Cell(long, long, long);
    void         Load();
    void         Unload();
    void         Render();
    
};

#endif
