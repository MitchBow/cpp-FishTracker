#include "App.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "VertebrateCreature.h"
#include "InvertebrateCreature.h"

App::App() : userBag(username, fishLimits, fishSizes) {
    loadFishLimits("saved.txt");
    printWelcomeMessage();
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    loadUserBag();
    std::cout << "---------------------\n";
}

void App::loadFishLimits(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open saved.txt!" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, sizeStr, vertebrateStr, limitStr;
    
        std::getline(ss, name, ',');
        std::getline(ss, sizeStr, ',');
        std::getline(ss, vertebrateStr, ',');
        std::getline(ss, limitStr, ',');
    
        try {
            int limit = std::stoi(limitStr);
            double size = std::stod(sizeStr);
            fishLimits[name] = limit;
            fishSizes[name] = size;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << "\n";
            continue;
        }
    }


    file.close();
}

void App::loadUserBag() {
    userBag = Bag::loadFromFile(username, "bags.txt", fishLimits, fishSizes);
}

void App::saveUserBag() {
    userBag.saveToFile("bags.txt");
}

void App::clearBag() {
    std::cout << "---------------------\n";
    char confirm;
    std::cout << "Are you sure you want to clear your bag? (y/n): \n";
    std::cout << "---------------------\n";
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        userBag.clearBag();
        saveUserBag();  // Save after clearing
    } else {
        std::cout << "Bag was not cleared.\n";
    }
    std::cout << "---------------------\n";
}

void App::printWelcomeMessage() const {
    std::cout << "Welcome to Sea++ \n";
    std::cout << "---------------------\n";
}

void App::printCloseMessage() const {
    std::cout << "---------------------\n";
    std::cout << "Thanks for using Sea++ \n";
}

void App::addToBag() {
    std::string fishName;
    double size;
    std::cout << "---------------------\n";
    std::cout << "Enter the fish name to add to your bag: ";
    std::getline(std::cin, fishName);
    std::cout << "Enter the size of the fish (in cm): ";
    std::cin >> size;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (userBag.addFish(fishName, size)) {
        saveUserBag();
    }


}

void App::viewBag() const {
    std::cout << "---------------------\n";
    userBag.viewBag();
    std::cout << "---------------------\n";
}

void App::createCreature() {
    std::string name;
    float size;
    bool carryingEggs;
    int amountLimit;
    bool isVertebrate;

    std::cout << "Enter name of creature: ";
    std::getline(std::cin, name);

    std::cout << "Enter size (in cm): ";
    while (!(std::cin >> size)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Is it carrying eggs? (1 for yes, 0 for no): ";
    while (!(std::cin >> carryingEggs)) {
        std::cout << "Invalid input. Please enter 1 or 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter amount limit (enter -1 for no limit): ";
    while (!(std::cin >> amountLimit)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Is this a vertebrate? (1 for yes, 0 for no): ";
    while (!(std::cin >> isVertebrate)) {
        std::cout << "Invalid input. Please enter 1 or 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (isVertebrate) {
        creatures.push_back(std::unique_ptr<SeaCreature>(new VertebrateCreature(name, size, carryingEggs, amountLimit)));
    } else {
        creatures.push_back(std::unique_ptr<SeaCreature>(new InvertebrateCreature(name, size, carryingEggs, amountLimit)));
    }

    // Debug: Print when a creature is created
    std::cout << "Created creature: " << name << ", Size: " << size << ", Vertebrate: " << (isVertebrate ? "Yes" : "No") << std::endl;
    std::cout << "---------------------\n";
}


void App::printAll() const {
    std::cout << "--- All Creatures ---\n";
    std::cout << "Name, Size minimum, Eggs, Limit, Type \n";
    
    // Debug: Check if creatures vector is empty
    if (creatures.empty()) {
        std::cout << "No creatures found!\n";
        std::cout << "---------------------\n";
    }

    for (const auto& creature : creatures) {
        std::string creatureInfo = creature->getInfo();
        
        // Debug: Print creature info

        if (auto vertebrate = dynamic_cast<VertebrateCreature*>(creature.get())) {
            creatureInfo += " (Vertebrate)";
        } else if (auto invertebrate = dynamic_cast<InvertebrateCreature*>(creature.get())) {
            creatureInfo += " (Invertebrate)";
        }

        std::cout << "-" << creatureInfo << std::endl;
    }
    std::cout << "---------------------\n";
}


void App::findCreature() const {
    std::string searchName;
    std::cout << "---------------------\n";
    std::cout << "Enter the name of the creature to find: ";
    std::cin >> searchName;

    for (const auto& creature : creatures) {
        std::string creatureInfo = creature->getInfo();

        if (auto vertebrate = dynamic_cast<VertebrateCreature*>(creature.get())) {
            creatureInfo += " (Vertebrate)";
        } else if (auto invertebrate = dynamic_cast<InvertebrateCreature*>(creature.get())) {
            creatureInfo += " (Invertebrate)";
        }

        if (creatureInfo.find(searchName) != std::string::npos) {
            std::cout << "Name, Size minimum, Eggs, Limit, Type \n";
            std::cout << "Found: " << creatureInfo << std::endl;
            std::cout << "---------------------\n";
            return;
        }
    }
    std::cout << "Creature not found.\n";
    std::cout << "---------------------\n";
}

void App::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);  // Use the filename here
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open " << filename << "!\n";  // Print error if file can't be opened
        return;
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, sizeStr, vertebrateStr, limitStr;
        float size;
        int isVertebrateInt, amountLimit;
        bool isVertebrate;
        bool carryingEggs = false;

        std::getline(ss, name, ',');
        name.erase(name.find_last_not_of(" \t\r\n") + 1);
        name.erase(0, name.find_first_not_of(" \t\r\n"));

        std::getline(ss, sizeStr, ',');
        std::getline(ss, vertebrateStr, ',');
        std::getline(ss, limitStr, ',');

        try {
            size = std::stof(sizeStr);  // Convert size to float
            isVertebrateInt = std::stoi(vertebrateStr);  // Convert vertebrate flag to integer
            amountLimit = std::stoi(limitStr);  // Convert limit to integer
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << "\n";
            continue;  // Skip malformed lines
        }

        isVertebrate = (isVertebrateInt == 1);

        // Manually create unique pointers
        if (isVertebrate) {
            creatures.push_back(std::unique_ptr<SeaCreature>(new VertebrateCreature(name, size, carryingEggs, amountLimit)));
        } else {
            creatures.push_back(std::unique_ptr<SeaCreature>(new InvertebrateCreature(name, size, carryingEggs, amountLimit)));
        }
    }

    file.close();
    std::cout << "Loaded " << creatures.size() << " creatures from file.\n";  // Debug print
    std::cout << "---------------------\n";
}



void App::run() {
    loadFromFile("saved.txt");
    int choice;
    do {
        std::cout << "1. Create Creature\n2. Print All Creatures\n3. Find Creature\n4. View Bag\n5. Add Fish to Bag\n6. Clear Bag\n7. Exit and Save\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: createCreature(); break;
            case 2: printAll(); break;
            case 3: findCreature(); break;
            case 4: viewBag(); break;
            case 5: addToBag(); break;
            case 6: clearBag(); break;
            case 7: printCloseMessage(); break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}
