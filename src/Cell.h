#ifndef CELL_H
#define CELL_H

extern int CELL_SIZE;

class Cell {

  private:

  public:
    int x, z;
             Cell(int, int);
    void     Load();
    void     Unload();
    void     Render();
    
};

#endif
