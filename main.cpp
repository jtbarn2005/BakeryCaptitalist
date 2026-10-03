#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Abstract base class: derived bread types provide their own description.
class BreadType {
public:
    BreadType(std::string name, int clicksRequired, double payout, double cost)
        : name_(std::move(name)), clicksRequired_(clicksRequired),
          payout_(payout), cost_(cost) {}
    virtual ~BreadType() = default;
    virtual std::string description() const = 0;

    const std::string& name() const { return name_; }
    int clicksRequired() const { return clicksRequired_; }
    double payout() const { return payout_; }
    double cost() const { return cost_; }

private:
    std::string name_;
    int clicksRequired_;
    double payout_;
    double cost_;
};

class WhiteBread : public BreadType {
public:
    WhiteBread() : BreadType("Classic White Bread", 5, 8.00, 0.00) {}
    std::string description() const override { return "A dependable starter loaf."; }
};

class Sourdough : public BreadType {
public:
    Sourdough() : BreadType("Sourdough", 8, 22.00, 60.00) {}
    std::string description() const override { return "An artisan loaf with a better margin."; }
};

class CinnamonRoll : public BreadType {
public:
    CinnamonRoll() : BreadType("Cinnamon Roll", 12, 45.00, 180.00) {}
    std::string description() const override { return "A sweet bestseller."; }
};

class Baguette : public BreadType {
public:
    Baguette() : BreadType("Golden Baguette", 18, 90.00, 450.00) {}
    std::string description() const override { return "A premium bakery specialty."; }
};

class RyeBread : public BreadType {
public:
    RyeBread() : BreadType("Rye Bread", 25, 210.00, 1000.00) {}
    std::string description() const override { return "A hearty loaf with a rich, earthy flavor."; }
};

class Pretzel : public BreadType {
public:
    Pretzel() : BreadType("Soft Pretzel", 32, 340.00, 2200.00) {}
    std::string description() const override { return "A chewy, golden snack baked to perfection."; }
};

class Focaccia : public BreadType {
public:
    Focaccia() : BreadType("Herb Focaccia", 40, 520.00, 4500.00) {}
    std::string description() const override { return "An olive-oil loaf topped with fragrant herbs."; }
};

class Brioche : public BreadType {
public:
    Brioche() : BreadType("Brioche", 50, 800.00, 9000.00) {}
    std::string description() const override { return "A buttery, tender loaf for your finest customers."; }
};

class Croissant : public BreadType {
public:
    Croissant() : BreadType("Croissant", 65, 1250.00, 18000.00) {}
    std::string description() const override { return "A flaky pastry folded into many delicate layers."; }
};

class Bagel : public BreadType {
public:
    Bagel() : BreadType("Everything Bagel", 80, 1900.00, 35000.00) {}
    std::string description() const override { return "A classic chewy bagel covered in savory toppings."; }
};

class MultigrainBread : public BreadType {
public:
    MultigrainBread() : BreadType("Multigrain Bread", 100, 2900.00, 65000.00) {}
    std::string description() const override { return "A wholesome loaf packed with grains and seeds."; }
};

class ChocolateBabka : public BreadType {
public:
    ChocolateBabka() : BreadType("Chocolate Babka", 125, 4500.00, 120000.00) {}
    std::string description() const override { return "A rich chocolate-swirled showpiece for the bakery."; }
};

class BakeryGame {
public:
    BakeryGame() : money_(0.0), totalEarned_(0.0), clicksTowardLoaf_(0),
                   activeBread_(0), gameOver_(false) {
        breads_.push_back(std::make_unique<WhiteBread>());
        breads_.push_back(std::make_unique<Sourdough>());
        breads_.push_back(std::make_unique<CinnamonRoll>());
        breads_.push_back(std::make_unique<Baguette>());
        breads_.push_back(std::make_unique<RyeBread>());
        breads_.push_back(std::make_unique<Pretzel>());
        breads_.push_back(std::make_unique<Focaccia>());
        breads_.push_back(std::make_unique<Brioche>());
        breads_.push_back(std::make_unique<Croissant>());
        breads_.push_back(std::make_unique<Bagel>());
        breads_.push_back(std::make_unique<MultigrainBread>());
        breads_.push_back(std::make_unique<ChocolateBabka>());
        unlocked_.push_back(true);
        unlocked_.resize(breads_.size(), false);
        loadGame();
    }

    void run() {
        std::cout << "\nWelcome to Bakery Capitalist!\n"
                  << "Bake bread, earn money, and grow your bakery.\n";
        while (!gameOver_) { // LOOP: runs until the player quits.
            showStatus();
            showMenu();
            const int choice = readInt("Choose an option: ");

            // CONDITIONALS: route the player's menu choice.
            if (choice == 1) bakeClick();
            else if (choice == 2) chooseBread();
            else if (choice == 3) buyBread();
            else if (choice == 4) saveGame();
            else if (choice == 5) restartGame();
            else if (choice == 6) gameOver_ = true;
            else std::cout << "Please choose a number from 1 to 6.\n";
        }
        saveGame();
        std::cout << "\nThanks for playing! You earned $" << money_
                  << " and baked " << totalLoaves_ << " loaves.\n";
    }

private:
    std::vector<std::unique_ptr<BreadType>> breads_; // STL data structure.
    std::vector<bool> unlocked_;
    double money_;
    double totalEarned_;
    int clicksTowardLoaf_;
    int activeBread_;
    long long totalLoaves_ = 0;
    bool gameOver_;

    void showStatus() const {
        const BreadType& bread = *breads_[activeBread_];
        std::cout << "\n----------------------------------------\n"
                  << std::fixed << std::setprecision(2)
                  << "Cash: $" << money_ << " | Total earned: $" << totalEarned_
                  << "\nProduct: " << bread.name() << "\nProgress: "
                  << clicksTowardLoaf_ << "/" << bread.clicksRequired() << " clicks\n"
                  << "----------------------------------------\n";
        }

    void showMenu() const {
        std::cout << "1. Click to bake\n2. Change bread\n3. Buy a new bread type\n"
                  << "4. Save game\n5. Restart game\n6. Quit\n";
    }

    int readInt(const std::string& prompt) const {
        int value;
        while (true) { // LOOP: reject invalid input until a number is entered.
            std::cout << prompt;
            if (std::cin >> value) return value;
            std::cout << "Please enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void bakeClick() {
        const BreadType& bread = *breads_[activeBread_];
        ++clicksTowardLoaf_;
        std::cout << "You knead and bake... (" << clicksTowardLoaf_ << "/"
                  << bread.clicksRequired() << ")\n";
        if (clicksTowardLoaf_ >= bread.clicksRequired()) {
            clicksTowardLoaf_ = 0;
            money_ += bread.payout();
            totalEarned_ += bread.payout();
            ++totalLoaves_;
            std::cout << "Fresh " << bread.name() << " sold for $"
                      << bread.payout() << "!\n";
        }
    }

    void chooseBread() {
        std::cout << "\nAvailable bread types:\n";
        for (std::size_t i = 0; i < breads_.size(); ++i) {
            std::cout << i + 1 << ". " << breads_[i]->name();
            if (!unlocked_[i]) std::cout << " (locked)";
            else if (static_cast<int>(i) == activeBread_) std::cout << " (active)";
            std::cout << "\n";
        }
        const int selection = readInt("Select a bread (0 to cancel): ");
        if (selection == 0) return;
        const int index = selection - 1;
        if (index >= 0 && index < static_cast<int>(breads_.size()) && unlocked_[index]) {
            activeBread_ = index;
            clicksTowardLoaf_ = 0;
            std::cout << "Now baking " << breads_[index]->name() << ".\n";
        } else std::cout << "That bread is locked or does not exist.\n";
    }

    void buyBread() {
        std::cout << "\nBread shop:\n";
        for (std::size_t i = 0; i < breads_.size(); ++i) {
            if (unlocked_[i]) std::cout << i + 1 << ". " << breads_[i]->name() << " (owned)\n";
            else std::cout << i + 1 << ". " << breads_[i]->name() << " - $"
                            << breads_[i]->cost() << " | " << breads_[i]->description() << "\n";
        }
        const int selection = readInt("Buy which bread (0 to cancel): ");
        if (selection == 0) return;
        const int index = selection - 1;
        if (index < 0 || index >= static_cast<int>(breads_.size())) {
            std::cout << "That bread does not exist.\n";
        } else if (unlocked_[index]) {
            std::cout << "You already own that bread.\n";
        } else if (money_ < breads_[index]->cost()) {
            std::cout << "You need $" << breads_[index]->cost() - money_ << " more to buy it.\n";
        } else {
            money_ -= breads_[index]->cost();
            unlocked_[index] = true;
            std::cout << "Purchased " << breads_[index]->name() << "!\n";
        }
    }

    void restartGame() {
        money_ = 0.0;
        totalEarned_ = 0.0;
        clicksTowardLoaf_ = 0;
        activeBread_ = 0;
        totalLoaves_ = 0;
        for (std::size_t i = 0; i < unlocked_.size(); ++i) {
            unlocked_[i] = (i == 0);
        }
        std::cout << "Game restarted. Only Classic White Bread is unlocked.\n";
        saveGame();
    }

    void loadGame() {
        std::ifstream file("bakery_save.txt");
        std::string format;
        if (!(file >> format)) return;

        double loadedMoney = 0.0;
        double loadedTotalEarned = 0.0;
        long long loadedTotalLoaves = 0;
        int loadedActiveBread = 0;
        int loadedClicksTowardLoaf = 0;

        if (format == "BAKERY_SAVE_V2") {
            std::string unlockedStates;
            if (!(file >> loadedMoney >> loadedTotalEarned >> loadedTotalLoaves
                       >> loadedActiveBread >> loadedClicksTowardLoaf >> unlockedStates)
                || unlockedStates.size() != breads_.size()) {
                return;
            }

            std::vector<bool> loadedUnlocked;
            loadedUnlocked.reserve(unlockedStates.size());
            for (char state : unlockedStates) {
                if (state != '0' && state != '1') return;
                loadedUnlocked.push_back(state == '1');
            }
            if (loadedMoney < 0.0 || loadedTotalEarned < 0.0 || loadedTotalLoaves < 0
                || loadedActiveBread < 0
                || loadedActiveBread >= static_cast<int>(breads_.size())
                || loadedClicksTowardLoaf < 0
                || !loadedUnlocked[loadedActiveBread]
                || loadedClicksTowardLoaf >= breads_[loadedActiveBread]->clicksRequired()
                || !loadedUnlocked[0]) {
                return;
            }
            unlocked_ = std::move(loadedUnlocked);
            activeBread_ = loadedActiveBread;
            clicksTowardLoaf_ = loadedClicksTowardLoaf;
        } else {
            file.clear();
            file.seekg(0);
            if (!(file >> loadedMoney >> loadedTotalEarned >> loadedTotalLoaves)
                || loadedMoney < 0.0 || loadedTotalEarned < 0.0 || loadedTotalLoaves < 0) {
                return;
            }
        }

        money_ = loadedMoney;
        totalEarned_ = loadedTotalEarned;
        totalLoaves_ = loadedTotalLoaves;
        std::cout << "Loaded saved game from bakery_save.txt.\n";
    }

    void saveGame() const {
        std::ofstream file("bakery_save.txt");
        if (file) {
            file << "BAKERY_SAVE_V2\n" << std::setprecision(17)
                 << money_ << '\n' << totalEarned_ << '\n' << totalLoaves_ << '\n'
                 << activeBread_ << '\n' << clicksTowardLoaf_ << '\n';
            for (bool isUnlocked : unlocked_) file << (isUnlocked ? '1' : '0');
            file << '\n';
            std::cout << "Game saved to bakery_save.txt.\n";
        } else std::cout << "Unable to save the game.\n";
    }
};

int main() {
    BakeryGame game;
    game.run();
    return 0;
}

