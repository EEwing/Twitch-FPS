#include "Event.h"

std::vector<void (*)(Event *)> Event::handles;

Event::Event() {
    isCancelled = false;
}

void Event::AddEventHandler(void (*execute)(Event *)) {

    handles.push_back(execute);

}

void Event::CallEvent() {

    for(int i=0; i<handles.size(); i++) {
        handles[i](this);
    }
    
    if(!isCancelled) {
        Execute();
    }

}
