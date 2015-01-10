#ifndef CELL_COLUMN_H
#define CELL_COLUMN_H

#include <vector>

#include "Cell.h"
#include "World.h"

class CellColumn {
  public:
    long x, z;
    std::vector<Cell> cells;
            CellColumn(long, long);
    void    Load();
    void    Unload();
    void    Render();
};

#endif
