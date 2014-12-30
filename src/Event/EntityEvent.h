#ifndef ENTITY_EVENT_H
#define ENTITY_EVENT_H

#include "Entity/Entity.h"
#include "Event/Event.h"

class EntityEvent : public Event {

  protected:
    Entity *entity;

};

#endif
