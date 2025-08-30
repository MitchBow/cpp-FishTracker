#ifndef SEACREATURE_H
#define SEACREATURE_H

#include <string>  // Add this to avoid 'string' type errors

class SeaCreature {
protected:
    std::string name;
    int size;
    bool carryingEggs;
    int amountLimit;

public:
    SeaCreature(const std::string& name, int size, bool carryingEggs, int amountLimit = -1)
        : name(name), size(size), carryingEggs(carryingEggs), amountLimit(amountLimit) {}

    virtual std::string getInfo() const {
        return name + ", " + std::to_string(size) + "cm, " + (carryingEggs ? "Carrying Eggs" : "Not Carrying Eggs") + ", " + (amountLimit >= 0 ? std::to_string(amountLimit) : "N/A");
    }

    virtual std::string getType() const = 0;  // Pure virtual function
};

#endif // SEACREATURE_H
