#include "World.h"

#include <cmath>

#include "Vector.h"

int RENDER_DISTANCE = 5;

World::World(void) {

}

void World::LoadArea(Player p) {

    //Wipe out any bits that are too far away
    Vector location = p.GetLocation();
    for(int i=0; i<renderedAreas.size(); i++) {
        if(std::abs(renderedAreas[i].x-location.x) > CELL_SIZE*RENDER_DISTANCE ||
           std::abs(renderedAreas[i].z-location.z) > CELL_SIZE*RENDER_DISTANCE) {
            renderedAreas[i].Unload();
            renderedAreas.erase(renderedAreas.begin() + i);
        }
    }
    
    //Load any new areas
    for(int i=-RENDER_DISTANCE; i<RENDER_DISTANCE; i++) {
        for(int j=-RENDER_DISTANCE; j<RENDER_DISTANCE; j++) {
            bool isLoaded = false;
            for(int k=0; k<renderedAreas.size(); k++) {
                if(location.x+i*CELL_SIZE >= renderedAreas[k].x && 
                   location.x+i*CELL_SIZE < renderedAreas[k].x+CELL_SIZE &&
                   location.z+j*CELL_SIZE >= renderedAreas[k].z &&
                   location.z+j*CELL_SIZE < renderedAreas[k].z+CELL_SIZE) {
                    isLoaded = true;
                    break;
                }
            }
            if(!isLoaded) {
                renderedAreas.push_back(Cell(location.x+i*CELL_SIZE, location.z+j*CELL_SIZE));
            }
        }
    }

}

void World::Render() {
    for(int i=0; i<renderedAreas.size(); i++) {
        renderedAreas[i].Render();
    }
}
