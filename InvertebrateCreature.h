#ifndef INVERTEBRATECREATURE_H
#define INVERTEBRATECREATURE_H

#include "SeaCreature.h"
#include <string>  // Add this to avoid 'string' type errors

class InvertebrateCreature : public SeaCreature {
public:
    InvertebrateCreature(const std::string& name, float size, bool carryingEggs, int amountLimit = -1)
        : SeaCreature(name, size, carryingEggs, amountLimit) {}

    std::string getType() const override {
        return "Invertebrate";
    }
};

#endif // INVERTEBRATECREATURE_H
