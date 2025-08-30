#ifndef BAG_H
#define BAG_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility> // for std::pair

class Bag {
private:
    std::string username;
    std::unordered_map<std::string, int> fishLimits; // max number per fish type
    std::unordered_map<std::string, double> fishSizes; // min size per fish type
    std::vector<std::pair<std::string, double>> fishList; // fish name + size

public:
    // Updated constructor with both limits and size map
    Bag(const std::string& user,
        const std::unordered_map<std::string, int>& limits,
        const std::unordered_map<std::string, double>& sizes);

    // Updated addFish function to accept a size
    bool addFish(const std::string& fishName, double size);

    void viewBag() const;
    void saveToFile(const std::string& filename) const;

    static Bag loadFromFile(const std::string& username,
                            const std::string& filename,
                            const std::unordered_map<std::string, int>& limits,
                            const std::unordered_map<std::string, double>& sizes);

    void clearBag();
};

#endif
