#include "Cell.h"

#include <stdio.h>

#include <iostream>
#include <cassert>
#include <cmath>

#include <GL/glew.h>

#include "MarchingCubes.h"
#include "Triangle.h"
#include "Vector.h"

double CELL_SIZE = 1.;

Vector Cell::corners[8] = {
    Vector(0,0,0),
    Vector(0,1,0),
    Vector(1,1,0),
    Vector(1,0,0),
    Vector(0,0,1),
    Vector(0,1,1),
    Vector(1,1,1),
    Vector(1,0,1)
};

Cell::Cell(long x, long y, long z) {
    cellX = x;
    cellY = y;
    cellZ = z;
    CalculateCase();
    render = false;
}

void Cell::Load() {
  //  if(cellCase == 153) {
   //     render = true;
        SetupPolygons();
        //fprintf(stderr, "cell %ld %ld %ld loads %d polygons\n", cellX, cellY, cellZ, triangles.size());
    //}
}

void Cell::Unload() {
    render = false;
}

void Cell::Render() {
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 0, 1);
    //if(render) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, &vertices.front());
        glDrawElements(GL_TRIANGLES, triangles.size()*3, GL_UNSIGNED_INT, &triangles.front());
        glDisableClientState(GL_VERTEX_ARRAY);
        /*
        glBegin(GL_QUADS);
          glNormal3f(0, 1, 0);
          glVertex3f(loc.x,           loc.y, loc.z          );
          glVertex3f(loc.x+CELL_SIZE, loc.y, loc.z          );
          glVertex3f(loc.x+CELL_SIZE, loc.y, loc.z+CELL_SIZE);
          glVertex3f(loc.x,           loc.y, loc.z+CELL_SIZE);
        glEnd();
        */
    //}
}

void Cell::CalculateCase() {
    for(int i=0; i<8; i++) {
        density[i] = GetDensity(corners[i]);
    }
    unsigned char result = 0;
    for(int i=0; i<8; i++) {
        result |= (density[i] >= 0) << i;
    }
    cellCase = result;
    //fprintf(stderr, "Case is: %u\n", (unsigned) cellCase);
}

Vector findZero(Vector v1, Vector v2, double val1, double val2) {
    return (v1 + (v2-v1)*(-val1 / (val2 - val1)));
}

int Cell::SetupPolygons() {
    Vector loc = Vector(cellX, cellY, cellZ)*CELL_SIZE;
    // interpolated vertices
	Vector InterpVertices[12];
	//Vector NewInterpVertices[12];
	signed char LocalRemap[12];
	
	//Cube is entirely in/out of the surface
	if (MarchingCubes::edgeTable[cellCase] == 0)
		return(0);

	//Find the vertices where the surface intersects the cube
	if (MarchingCubes::edgeTable[cellCase] & 1)
		InterpVertices[0] =
			findZero(Cell::corners[0],Cell::corners[1],density[0],density[1]);
	if (MarchingCubes::edgeTable[cellCase] & 2)
		InterpVertices[1] =
			findZero(Cell::corners[1],Cell::corners[2],density[1],density[2]);
	if (MarchingCubes::edgeTable[cellCase] & 4)
		InterpVertices[2] =
			findZero(Cell::corners[2],Cell::corners[3],density[2],density[3]);
	if (MarchingCubes::edgeTable[cellCase] & 8)
		InterpVertices[3] =
			findZero(Cell::corners[3],Cell::corners[0],density[3],density[0]);
	if (MarchingCubes::edgeTable[cellCase] & 16)
		InterpVertices[4] =
			findZero(Cell::corners[4],Cell::corners[5],density[4],density[5]);
	if (MarchingCubes::edgeTable[cellCase] & 32)
		InterpVertices[5] =
			findZero(Cell::corners[5],Cell::corners[6],density[5],density[6]);
	if (MarchingCubes::edgeTable[cellCase] & 64)
		InterpVertices[6] =
			findZero(Cell::corners[6],Cell::corners[7],density[6],density[7]);
	if (MarchingCubes::edgeTable[cellCase] & 128)
		InterpVertices[7] =
			findZero(Cell::corners[7],Cell::corners[4],density[7],density[4]);
	if (MarchingCubes::edgeTable[cellCase] & 256)
		InterpVertices[8] =
			findZero(Cell::corners[0],Cell::corners[4],density[0],density[4]);
	if (MarchingCubes::edgeTable[cellCase] & 512)
		InterpVertices[9] =
			findZero(Cell::corners[1],Cell::corners[5],density[1],density[5]);
	if (MarchingCubes::edgeTable[cellCase] & 1024)
		InterpVertices[10] =
			findZero(Cell::corners[2],Cell::corners[6],density[2],density[6]);
	if (MarchingCubes::edgeTable[cellCase] & 2048)
        InterpVertices[11] =
			findZero(Cell::corners[3],Cell::corners[7],density[3],density[7]);

	for (int i=0;i<12;i++)
		LocalRemap[i] = -1;

    vertices.clear();
	for (int i=0;MarchingCubes::triTable[cellCase][i]!=-1;i++)
	{
		if(LocalRemap[MarchingCubes::triTable[cellCase][i]] == -1)
		{
            vertices.push_back(InterpVertices[MarchingCubes::triTable[cellCase][i]] + loc);
			LocalRemap[MarchingCubes::triTable[cellCase][i]] = vertices.size()-1;
		}
	}

    triangles.clear();
	for (int i=0;MarchingCubes::triTable[cellCase][i]!=-1;i+=3) {
        Triangle t;
        t[0] = LocalRemap[MarchingCubes::triTable[cellCase][i+0]];
        t[1] = LocalRemap[MarchingCubes::triTable[cellCase][i+1]];
        t[2] = LocalRemap[MarchingCubes::triTable[cellCase][i+2]];
        triangles.push_back(t);
	}

	return(triangles.size());
}

double Cell::GetDensity(double ratioX, double ratioY, double ratioZ) {
    assert(ratioX >=0. && ratioX<=1.);
    assert(ratioY >=0. && ratioY<=1.);
    assert(ratioZ >=0. && ratioZ<=1.);

    Vector wLoc = Vector(cellX+ratioX, cellY+ratioY, cellZ+ratioZ)*CELL_SIZE;
    double rtn = -(wLoc.y)+sin(wLoc.x)*.5*cos(wLoc.z);
    //rtn = 5-wLoc.GetMagnitude();

    //fprintf(stderr, "cellY = %d\n", cellY);
    //fprintf(stderr, "Density @ %lf %lf %lf = %lf\n", wLoc.x, wLoc.y, wLoc.z, rtn);
    return rtn;
}

double Cell::GetDensity(Vector v) {
    return GetDensity(v.x, v.y, v.z);
}

void Cell::init() {
}
