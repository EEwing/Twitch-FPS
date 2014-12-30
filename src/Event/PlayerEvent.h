#ifndef PLAYER_EVENT_H
#define PLAYER_EVENT_H

#include "Entity/Player.h"
#include "Event/EntityEvent.h"

class PlayerEvent : public EntityEvent {
  protected:
    Player *player;

  public:
    PlayerEvent(Player *);

};

#endif
