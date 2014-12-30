#include "PlayerMoveEvent.h"

#include <stdio.h>

PlayerMoveEvent::PlayerMoveEvent(Player *p, Vector toLocation, Vector fromLocation) : PlayerEvent(p) {
    this->toLocation = toLocation;
    this->fromLocation = fromLocation;
}

PlayerMoveEvent::PlayerMoveEvent(Player *p, Vector toLocation) : PlayerEvent(p) {
    this->toLocation = toLocation;
    this->fromLocation = p->GetLocation();
}

void PlayerMoveEvent::Execute() {
    player->Teleport(toLocation);
    //fprintf(stderr, "Executing a PlayerMoveEvent\n");
}
