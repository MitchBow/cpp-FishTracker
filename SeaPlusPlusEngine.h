#ifndef SEAPLUSPLUSENGINE_H
#define SEAPLUSPLUSENGINE_H

#include "VertebrateChecker.h"
#include "InvertebrateChecker.h"
#include "SeaCreature.h"

class SeaPlusPlusEngine {
public:
    SeaPlusPlusEngine();
    void processSeaCreatures();
private:
    VertebrateChecker vertebrateChecker;
    InvertebrateChecker invertebrateChecker;
};

#endif // SEAPLUSPLUSENGINE_H
