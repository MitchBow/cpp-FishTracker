#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>    
#include <memory>    
#include <limits>    
#include <string>
#include <unordered_map>
#include "Bag.h"
#include "SeaCreature.h"

class App {
private:
    std::unordered_map<std::string, int> fishLimits;
    std::unordered_map<std::string, double> fishSizes; // <-- NEW
    std::string username;
    Bag userBag;
    std::vector<std::unique_ptr<SeaCreature>> creatures;

    void loadFishLimits(const std::string& filename);
    void createCreature();
    void printAll() const;
    void findCreature() const;

public:
    App();
    void printWelcomeMessage() const;
    void printCloseMessage() const;
    void loadFromFile(const std::string& filename);
    void loadUserBag();
    void saveUserBag();
    void addToBag();
    void viewBag() const;
    void run();  
    void clearBag();
};

#endif
