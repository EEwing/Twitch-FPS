#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "CellColumn.h"
#include "Entity/Player.h"

class CellColumn;

extern int LOAD_DISTANCE;
extern int UNLOAD_DISTANCE;

class World {

  private:
    int id;
    std::vector<CellColumn *> renderedAreas;

  public:
    static const int WORLD_HEIGHT;
             World(void);

    void     LoadArea(Player &);
    void     Render();
};

#endif
