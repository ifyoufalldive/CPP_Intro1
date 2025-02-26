// Author: Francesca Guerrero
// Assignment 9: Noah's Ark Game
// Date Submitted: 12/11/2024


#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Base Animal class
class Animal {
protected:
    string species;
    string gender;
    int age;

public:
    Animal(const string& species, const string& gender, int age)
        : species(species), gender(gender), age(age) {}

    virtual ~Animal() = default;

    virtual bool canGiveBirth() const = 0;
    virtual shared_ptr<Animal> createOffspring() const = 0;

    void ageOneMonth() { age++; }

    string getDescription() const {
        return "I am a " + gender + " " + species + ", " + to_string(age) + " months old";
    }

    string getGender() const { return gender; }

    int getAge() const { return age; }
};

// Mammal class
class Mammal : public Animal {
public:
    Mammal(const string& species, const string& gender, int age)
        : Animal(species, gender, age) {}

    bool canGiveBirth() const override {
        return gender == "female" && age > 0 && age % 12 == 0;
    }

    shared_ptr<Animal> createOffspring() const override {
        string offspringGender = (rand() % 2 == 0) ? "male" : "female";
        return make_shared<Mammal>(species, offspringGender, 0);
    }
};

// Bird class
class Bird : public Animal {
public:
    Bird(const string& species, const string& gender, int age)
        : Animal(species, gender, age) {}

    bool canGiveBirth() const override {
        return gender == "female" && age > 0 && age % 9 == 0;
    }

    shared_ptr<Animal> createOffspring() const override {
        string offspringGender = (rand() % 2 == 0) ? "male" : "female";
        return make_shared<Bird>(species, offspringGender, 0);
    }
};

// Fish class
class Fish : public Animal {
public:
    Fish(const string& species, const string& gender, int age)
        : Animal(species, gender, age) {}

    bool canGiveBirth() const override {
        return gender == "female" && age > 0 && age % 6 == 0;
    }

    shared_ptr<Animal> createOffspring() const override {
        string offspringGender = (rand() % 2 == 0) ? "male" : "female";
        return make_shared<Fish>(species, offspringGender, 0);
    }
};

// Ark Inventory Management
class Ark {
private:
    vector<shared_ptr<Animal>> animals;
    int monthsOnArk;
    int food;
    int water;
    int space;
    bool scavengedThisYear;

    void annualCull() {
        if (monthsOnArk % 12 == 0 && animals.size() > 5) {
            // Cull 5 oldest animals
            sort(animals.begin(), animals.end(), [](const shared_ptr<Animal>& a, const shared_ptr<Animal>& b) {
                return a->getAge() > b->getAge();
                });

            cout << "Annual cull performed. Removing 5 oldest animals.\n";
            animals.erase(animals.end() - 5, animals.end());

            // Add resources back
            food += 50;
            water += 50;
            cout << "Resources replenished: +50 food, +50 water.\n";
        }
    }

public:
    Ark() : monthsOnArk(0), food(1000), water(1000), space(500), scavengedThisYear(false) {
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
        // Initialize animals
        animals.push_back(make_shared<Mammal>("cat", "female", 0));
        animals.push_back(make_shared<Mammal>("cat", "male", 0));
        animals.push_back(make_shared<Mammal>("dog", "female", 0));
        animals.push_back(make_shared<Mammal>("dog", "male", 0));
        animals.push_back(make_shared<Bird>("eagle", "female", 0));
        animals.push_back(make_shared<Bird>("eagle", "male", 0));
        animals.push_back(make_shared<Bird>("parakeet", "female", 0));
        animals.push_back(make_shared<Bird>("parakeet", "male", 0));
        animals.push_back(make_shared<Fish>("goldfish", "female", 0));
        animals.push_back(make_shared<Fish>("goldfish", "male", 0));
        animals.push_back(make_shared<Fish>("shark", "female", 0));
        animals.push_back(make_shared<Fish>("shark", "male", 0));
    }

    bool ageAnimals() {
        monthsOnArk++;
        vector<shared_ptr<Animal>> newAnimals;

        for (const auto& animal : animals) {
            animal->ageOneMonth();
            if (animal->canGiveBirth()) {
                newAnimals.push_back(animal->createOffspring());
            }
        }

        animals.insert(animals.end(), newAnimals.begin(), newAnimals.end());

        // Resource consumption
        int totalConsumption = animals.size();
        food -= totalConsumption;
        water -= totalConsumption;
        space -= totalConsumption;

        // Annual cull
        annualCull();

        // Reset scavenging flag annually
        if (monthsOnArk % 12 == 0) {
            scavengedThisYear = false;
        }

        // Check if resources are depleted
        if (food <= 0 || water <= 0 || space <= 0) {
            cout << "Critical resource depletion! The ark can no longer sustain the population.\n\n";
            return false; // Indicate failure
        }

        return true; // Indicate success
    }

    void showInventory() const {
        cout << "Animal inventory:\n";
        for (size_t i = 0; i < animals.size(); ++i) {
            cout << "Animal #" << i + 1 << ": " << animals[i]->getDescription() << endl;
        }
    }

    void showResources() const {
        cout << "Resource inventory:\n";
        cout << "Food: " << food << "\n";
        cout << "Water: " << water << "\n";
        cout << "Space: " << space << "\n";
    }

    void scavengeResources() {
        if (scavengedThisYear) {
            cout << "You can only scavenge once per year!\n";
            return;
        }

        cout << "Scavenging for resources...\n";
        food += 100;
        water += 100;
        space += 50;
        scavengedThisYear = true;

        cout << "Scavenging successful: +100 food, +100 water, +50 space.\n";
    }

    int getMonthsOnArk() const { return monthsOnArk; }
};

int main() {
    Ark ark;
    int choice;

    do {
        cout << "You have been on the ark for " << ark.getMonthsOnArk() << " months. Would you like to:\n";
        cout << "1 - Let another month pass\n";
        cout << "2 - Check animal inventory\n";
        cout << "3 - View resource inventory\n";
        cout << "4 - Scavenge for resources\n";
        cout << "5 - Quit\n";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 5:\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            if (!ark.ageAnimals()) {
                cout << "The ark can no longer support the animals after " << ark.getMonthsOnArk() << " months." << endl;
                choice = 5; // Exit simulation
            }
            break;
        case 2:
            ark.showInventory();
            break;
        case 3:
            ark.showResources();
            break;
        case 4:
            ark.scavengeResources();
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please select again.\n";
        }
    } while (choice != 5);

    return 0;
}