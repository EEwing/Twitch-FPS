#include "World.h"

#include <stdio.h>

#include <algorithm>
#include <cmath>

#include "Cell.h"
#include "Vector.h"

int LOAD_DISTANCE = 10;
int UNLOAD_DISTANCE = 12;
const int World::WORLD_HEIGHT = 100; // measured in #s of cells

World::World(void) {

}

void World::LoadArea(Player &p) {

    //Wipe out any cells that are too far away
    //Vector location = p.GetLocation();
    long playerCellX, playerCellZ;
    playerCellX = floor(p.GetLocation().x/CELL_SIZE);
    playerCellZ = floor(p.GetLocation().z/CELL_SIZE);

    int unloadedChunks = 0;
    for(int i=0; i<renderedAreas.size(); ++i) {
        if(std::abs(renderedAreas[i]->x-playerCellX) > UNLOAD_DISTANCE ||
           std::abs(renderedAreas[i]->z-playerCellZ) > UNLOAD_DISTANCE) {
            renderedAreas[i]->Unload();
            delete renderedAreas[i];
            renderedAreas[i] = NULL;
            ++unloadedChunks;
        }
    }

    renderedAreas.erase( std::remove(renderedAreas.begin(), renderedAreas.end(), (CellColumn *) NULL), 
                         renderedAreas.end());


    //Load any new areas
    int newLoadedChunks = 0;
    for(int i=-LOAD_DISTANCE; i<=LOAD_DISTANCE; i++) {
        for(int j=-LOAD_DISTANCE; j<=LOAD_DISTANCE; j++) {
            bool isLoaded = false;
            for(int k=0; k<renderedAreas.size(); k++) {
                if( playerCellX+i >= renderedAreas[k]->x   && 
                    playerCellX+i <  renderedAreas[k]->x+1 &&
                    playerCellZ+j >= renderedAreas[k]->z   &&
                    playerCellZ+j <  renderedAreas[k]->z+1 ) {
                    isLoaded = true;
                    break;
                }
            }
            if(!isLoaded) {
                CellColumn *c = new CellColumn(playerCellX+i, playerCellZ+j);
                c->Load();
                renderedAreas.push_back(c);
                ++newLoadedChunks;
            }
        }
    }
    /*
    fprintf(stderr, "Player location: %lf %lf\n", p.GetLocation().x, p.GetLocation().z);
    fprintf(stderr, "===========\n");
    for(int i=0; i<renderedAreas.size(); i++)
        fprintf(stderr, "%ld %ld\n", renderedAreas[i]->x, renderedAreas[i]->z);
    fprintf(stderr, "===========\n");
    fprintf(stderr, "Columns loaded: %d\n", newLoadedChunks);
    fprintf(stderr, "Columns unloaded: %d\n", unloadedChunks);
    fprintf(stderr, "Total Columns in memory: %d\n", renderedAreas.size());
    */
}

void World::Render() {
    //fprintf(stderr, "Rendering %d columns\n", renderedAreas.size());
    for(int i=0; i<renderedAreas.size(); i++) {
        renderedAreas[i]->Render();
    }
}
