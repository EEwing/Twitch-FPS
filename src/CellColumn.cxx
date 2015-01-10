#include "CellColumn.h"

#include <stdio.h>

CellColumn::CellColumn(long x, long z) {

    this->x = x;
    this->z = z;

    for(int i=-World::WORLD_HEIGHT; i<World::WORLD_HEIGHT; i++) {
        cells.push_back(Cell(x, i, z));
    }

}

void CellColumn::Load() {
    for(int i=0; i<cells.size(); i++) {
        cells[i].Load();
    }
}

void CellColumn::Unload() {
    for(int i=0; i<cells.size(); i++) {
        cells[i].Unload();
    }
}

void CellColumn::Render() {
    for(int i=0; i<cells.size(); i++) {
        cells[i].Render();
    }
}
