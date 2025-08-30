#ifndef VERTEBRATECREATURE_H
#define VERTEBRATECREATURE_H

#include "SeaCreature.h"
#include <string>  // Add this to avoid 'string' type errors

class VertebrateCreature : public SeaCreature {
public:
    VertebrateCreature(const std::string& name, float size, bool carryingEggs, int amountLimit = -1)
        : SeaCreature(name, size, carryingEggs, amountLimit) {}

    std::string getType() const override {
        return "Vertebrate";
    }
};

#endif // VERTEBRATECREATURE_H
