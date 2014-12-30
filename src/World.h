#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Cell.h"
#include "Entity/Player.h"

extern int RENDER_DISTANCE;

class World {

  private:
    int id;
    std::vector<Cell> renderedAreas;

  public:
             World(void);

    void     LoadArea(Player);
    void     Render();
};

#endif
