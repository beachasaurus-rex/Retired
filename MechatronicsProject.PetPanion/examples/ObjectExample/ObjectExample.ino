#ifndef thing
    #define thing
    #include "ObjectExample.hpp"
#endif
#ifndef things
    #define things
    #include "ObjectExample.cpp"
#endif

ObjectExample* ex;

void setup()
{
    Serial.begin(9600);
    ex = new ObjectExample();
    Serial.println(ex->DoThing());
}

void loop()
{

}
