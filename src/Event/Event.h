#ifndef EVENT_H
#define EVENT_H

#include <vector>

class Event {

  private:
    static std::vector<void (*)(Event *)> handles;
    virtual void     Execute() = 0;

  public:
    bool             isCancelled;

                     Event();
    static void      AddEventHandler(void (*)(Event *));
    void             CallEvent();

};

#endif

