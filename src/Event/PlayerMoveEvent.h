#ifndef PLAYER_MOVE_EVENT_H
#define PLAYER_MOVE_EVENT_H

#include "Event/PlayerEvent.h"

class PlayerMoveEvent : public PlayerEvent {
  private:
    virtual void     Execute();
    
  public:
             PlayerMoveEvent(Player *, Vector, Vector);
             PlayerMoveEvent(Player *, Vector);
    Vector toLocation;
    Vector fromLocation;


};

#endif
