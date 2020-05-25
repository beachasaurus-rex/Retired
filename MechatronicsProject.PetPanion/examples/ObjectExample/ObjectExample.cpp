#ifndef thing
    #define thing
    #include "ObjectExample.hpp"
#endif

ObjectExample::ObjectExample()
{
    this->DontTouchMe = 9;
}

int ObjectExample::DoThing()
{
    return this->DontTouchMe;
}
