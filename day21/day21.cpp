/**
 * @file    day21.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    21 Dec 2020
 * @bug     
 * @todo    
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


namespace day21 {

struct MenuEntry {
    std::set<std::string> * ingredientList;
    std::set<std::string> * allergensList;
};

class Menu {
public:
    Menu(std::string inputFilename);
    uint64_t countNotAllergen();
    std::string printIngredients();
private:
    std::unordered_map<std::string, uint64_t> ingredientPresence;
    std::vector<MenuEntry> foodList;
    std::set<std::string> allAllergens;
    std::set<std::string> allIngredients;

    std::map<std::string, std::string> allergenIsIngredient;
    std::set<std::string> safeIngredients;

    void readLine(std::string line);
    void calculateData();
};

uint64_t process1(std::string file);
std::string process2(std::string file);

} // namespace day21


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day21::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day21::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day21::process1(std::string file) {
    Menu menu(file);
    return menu.countNotAllergen();
}


std::string day21::process2(std::string file) {
    Menu menu(file);
    return menu.printIngredients();
}


// ===== ===== ===== Implementations ===== ===== ===== 

day21::Menu::Menu(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            readLine(part);
        }
    }
    calculateData();
}


void day21::Menu::readLine(std::string line) {
    size_t pos = 0;
    size_t stop;
    size_t end = line.find("(", pos);
    // Ingredients
    std::set<std::string> * ingredientsSorted = new std::set<std::string>();
    stop = line.find(' ', pos);
    while (stop < end) {
        std::string ingredient = line.substr(pos, stop-pos);
        // Add to all ingredient
        allIngredients.insert(ingredient);
        // Add to list
        ingredientsSorted->insert(ingredient);
        // Add presence
        auto found = ingredientPresence.find(ingredient);
        if (found != ingredientPresence.end()) {
            found->second = found->second + 1;
        } else {
            ingredientPresence.insert(make_pair(ingredient, 1));
        }
        // Next
        pos = stop + 1;
        stop = line.find(' ', pos);
    }

    // Allergens
    std::set<std::string> * allergensSorted = new std::set<std::string>();
    pos = line.find(' ', end) + 1;
    stop = line.find(',', pos);
    if (stop == std::string::npos) {
        stop = line.find(')', pos);
    }
    while (stop != std::string::npos) {
        std::string allergen = line.substr(pos, stop-pos);
        // Add to all allergens
        allAllergens.insert(allergen);
        // Add to list
        allergensSorted->insert(allergen);
        // Next
        pos = stop + 2;
        stop = line.find(',', pos);
        if (stop == std::string::npos) {
            stop = line.find(')', pos);
        }
    }
    MenuEntry food;
    food.allergensList = allergensSorted;
    food.ingredientList = ingredientsSorted;
    foodList.push_back(food);
}


void day21::Menu::calculateData() {
    // Map allergen to possible ingredients
    std::unordered_map<std::string, std::set<std::string>*> allergenToIngredients;
    // For every allergen
    for(auto allergen : allAllergens) {
        // Create list of possible ingredients
        std::set<std::string>* ingredients = new std::set<std::string>();
        for(auto ing : allIngredients) {
            ingredients->insert(ing);
        }
        // Add entry map <allergen, ingredients>
        allergenToIngredients.insert(make_pair(allergen, ingredients));

        // For every food entry (menù line)
        for(auto food : foodList) {
            // Check if allergen is in this food
            bool found = false;
            for (std::string foodAllergen : (*(food.allergensList))) {
                if (allergen == foodAllergen) {
                    found = true;
                    break;
                }
            }
            if (found) {
                // Intersect sets
                std::set<std::string>* intersection = new std::set<std::string>();
                auto it = allergenToIngredients.find(allergen);
                for (auto ing : *it->second) {
                    // Add to intersection if ingredient exists in both sets
                    if (food.ingredientList->find(ing) != food.ingredientList->end()) {
                        intersection->insert(ing);
                    }
                }

                // Save intersection
                it->second = intersection;
            }
        }
    }

    // Initializite safe ingredient list with all ingredient
    for (auto ing : allIngredients) {
        safeIngredients.insert(ing);
    }

    // Remove the ingredients matched to an allergen
    while (allergenToIngredients.size() > 0) { // precarious condition
        // Pick an ingredient
        auto entryToDelete = allergenToIngredients.end();
        for (auto it = allergenToIngredients.begin(); it != allergenToIngredients.end(); it++) {
            if (it->second->size() == 1) {
                entryToDelete = it;
                break;
            }
        }
        if (entryToDelete == allergenToIngredients.end()) {
            // End if no allergen have ingredient list long 1
            break;
        }
        // Save ingredient and remove entry
        std::string ingredientToRemove = *(entryToDelete->second->begin());
        allergenIsIngredient.insert(make_pair(entryToDelete->first, ingredientToRemove));
        allergenToIngredients.erase(entryToDelete);

        // Remove the ingredient from all other allergens
        for (auto entry : allergenToIngredients) {
            auto it = entry.second->find(ingredientToRemove);
            if (it != entry.second->end()) {
                entry.second->erase(it);
            }
        }
        // Remove from safeingredient
        safeIngredients.erase(ingredientToRemove);
    }
}

uint64_t day21::Menu::countNotAllergen() {
    // Count remaning ingredients
    uint64_t sum = 0;
    for(auto ingredient : safeIngredients) {
        auto found = ingredientPresence.find(ingredient);
        if (found != ingredientPresence.end()) {
            sum += found->second;
        }
    }
    return sum;
}


std::string day21::Menu::printIngredients() {
    std::string list = "";
    for (auto entry : allergenIsIngredient) {
        list += entry.second + ",";
    }
    return list.substr(0, list.length()-1);
}