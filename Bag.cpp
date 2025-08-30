#include "Bag.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Bag::Bag(const std::string& user, const std::unordered_map<std::string, int>& limits,
         const std::unordered_map<std::string, double>& sizes)
    : username(user), fishLimits(limits), fishSizes(sizes) {}


bool Bag::addFish(const std::string& fishName, double size) {
    if (fishLimits.count(fishName) == 0 || fishSizes.count(fishName) == 0) {
        std::cout << "Creature '" << fishName << "' does not exist.\n";
        return false;
    }

    if (size < fishSizes.at(fishName)) {
        std::cout << "The " << fishName << " is too small. Minimum size is " << fishSizes.at(fishName) << ".\n";
        return false;
    }

    if (fishList.size() >= 20) {
        std::cout << "Bag is full (max 20 fish).\n";
        return false;
    }

    int currentCount = 0;
    for (const auto& entry : fishList) {
        if (entry.first == fishName) currentCount++;
    }

    int limit = fishLimits.at(fishName);
    if (limit != -1 && currentCount >= limit) {
        std::cout << "You can't add more " << fishName << ". Limit reached.\n";
        std::cout << "---------------------\n";
        return false;
    }

    fishList.emplace_back(fishName, size);
    std::cout << fishName << " (" << size << " cm) added to your bag.\n";
    return true;
}



void Bag::viewBag() const {
    std::cout << "Fish in bag for " << username << ":\n";
    if (fishList.empty()) {
        std::cout << "  (Bag is empty)\n";
        return;
    }

    std::unordered_map<std::string, std::vector<double>> grouped;
    for (const auto& pair : fishList) {
    const std::string& name = pair.first;
    double size = pair.second;
    std::cout << "- " << name << " (Size: " << size << " cm)" << std::endl;
    }


    for (const auto& pair : grouped) {
        std::cout << "  " << pair.first << ": " << pair.second.size() << " (sizes: ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i];
            if (i < pair.second.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
    }
}


void Bag::saveToFile(const std::string& filename) const {
    std::ifstream inFile(filename);
    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string userPart;
        if (std::getline(ss, userPart, '|') && userPart == username) {
            std::ostringstream updated;
            updated << username << "|";
            for (size_t i = 0; i < fishList.size(); ++i) {
                updated << fishList[i].first << ":" << fishList[i].second;
                if (i < fishList.size() - 1) updated << ",";
            }
            lines.push_back(updated.str());
            found = true;
        } else {
            lines.push_back(line);
        }
    }
    inFile.close();

    if (!found) {
        std::ostringstream newEntry;
        newEntry << username << "|";
        for (size_t i = 0; i < fishList.size(); ++i) {
            newEntry << fishList[i].first << ":" << fishList[i].second;
            if (i < fishList.size() - 1) newEntry << ",";
        }
        lines.push_back(newEntry.str());
    }

    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    std::cout << "Bag saved.\n";
}


Bag Bag::loadFromFile(const std::string& username, const std::string& filename,
                      const std::unordered_map<std::string, int>& limits,
                      const std::unordered_map<std::string, double>& sizes) {
    std::ifstream in(filename);
    std::string line;
    Bag bag(username, limits, sizes);

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string userPart, fishPart;
        if (std::getline(ss, userPart, '|') && userPart == username) {
            if (std::getline(ss, fishPart)) {
                std::istringstream fishStream(fishPart);
                std::string entry;
                while (std::getline(fishStream, entry, ',')) {
                    size_t sep = entry.find(':');
                    if (sep != std::string::npos) {
                        std::string name = entry.substr(0, sep);
                        double size = std::stod(entry.substr(sep + 1));
                        bag.fishList.emplace_back(name, size);
                    }
                }
            }
            break;
        }
    }

    return bag;
}


void Bag::clearBag() {
    fishList.clear();
    std::cout << "Your bag has been cleared.\n";
}
