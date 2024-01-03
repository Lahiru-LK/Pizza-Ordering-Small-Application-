#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Topping {
public:
    string name;
    double price;

    Topping(const string& n, double p) : name(n), price(p) {}
};

class Order {
public:
    string size;
    vector<Topping> toppings;
    double totalPrice;

    Order() : size(""), totalPrice(0.0) {}

    void addTopping(const Topping& topping) {
        toppings.push_back(topping);
        totalPrice += topping.price;
    }
};

class PizzaMenu {
public:
    static vector<Topping> getToppings() {
        return {
                {"Ham", 0.80},
                {"Mushrooms", 0.50},
                {"Pepperoni", 1.00},
                {"Peppers", 0.80},
                {"Onions", 0.40},
                {"Extra Cheese", 1.50}
        };
    }
};

class PizzaSystem {
private:
    double credits;
    vector<Order> recentOrders;

public:
    PizzaSystem() : credits(0.0) {}

    void displayMainMenu() const;
    void addCredits();
    void orderPizza(Order& order);
    void checkout(Order& order);
    void displayRecentOrders() const;
};

void PizzaSystem::displayMainMenu() const {
    cout << "-------------------------------" << endl;
    cout << "UCLan PIZZA" << endl;
    cout << "-------------------------------" << endl;
    cout << "MAIN MENU" << endl;
    cout << " 1. Add Credits (current credits = " << fixed << setprecision(2) << credits << ")\n";
    cout << " 2. Order Pizza\n";
    cout << " 3. Checkout\n";
    cout << " 4. Recent Orders\n";
    cout << " 0. Exit\n\n";
    cout << "Please enter a number: ";
}

void PizzaSystem::addCredits() {
    double amount;
    cout << "Enter the amount to add to your credits: ";
    cin >> amount;
    credits += amount;
    cout << "Your new balance = " << fixed << setprecision(2) << credits << " credits\n";
}

void PizzaSystem::orderPizza(Order& order) {
    cout << "\nORDER PIZZA - Select Size [Current Balance = " << fixed << setprecision(2) << credits << " credits]\n\n";
    cout << "Please choose from the following options:\n";
    cout << " 1. Small [5.0 credits]\n";
    cout << " 2. Medium [8.50 credits]\n";
    cout << " 3. Large [10.25 credits]\n";
    cout << " 0. Return to Main Menu\n";
    cout << "........................................\n";
    cout << "Please enter a number: ";

    int sizeChoice;
    cin >> sizeChoice;
    if (sizeChoice == 0) {
        return;
    }

    order.size = (sizeChoice == 1) ? "Small" : ((sizeChoice == 2) ? "Medium" : "Large");
    order.totalPrice += (sizeChoice == 1) ? 5.0 : ((sizeChoice == 2) ? 8.50 : 10.25);

    cout << "You have selected a " << order.size << " pizza.\n";
    cout << "........................................\n";

    cout << "ORDER PIZZA - Select Toppings\n";
    cout << "You have selected a " << order.size << " pizza.\n";
    cout << "Please choose from the following toppings:\n\n";

    vector<Topping> toppings = PizzaMenu::getToppings();

    for (int i = 0; i < toppings.size(); ++i) {
        cout << " " << i + 1 << ". " << toppings[i].name << " [" << fixed << setprecision(2) << toppings[i].price << " credits]\n";
    }

    cout << " 0. Return to Main Menu\n\n";
    cout << "........................................\n";
    cout << "Please enter a number: ";

    int toppingChoice;
    cin >> toppingChoice;
    if (toppingChoice == 0) {
        return;
    }

    order.addTopping(toppings[toppingChoice - 1]);

    cout << "You have added " << toppings[toppingChoice - 1].name << " to your pizza. Your current price is: " << fixed << setprecision(2) << order.totalPrice << " credits.\n";

    char addMoreToppings;
    cout << "Would you like to add additional toppings?\nPlease input 'Y' for yes and 'N' for no: ";
    cin >> addMoreToppings;

    while (addMoreToppings == 'Y' || addMoreToppings == 'y') {
        cout << "ORDER PIZZA - Select Toppings\n";
        cout << "You have selected a " << order.size << " pizza.\n";
        cout << "Please choose from the following toppings:\n\n";

        for (int i = 0; i < toppings.size(); ++i) {
            cout << " " << i + 1 << ". " << toppings[i].name << " [" << fixed << setprecision(2) << toppings[i].price << " credits]\n";
        }

        cout << " 0. Return to Main Menu\n\n";
        cout << "........................................\n";
        cout << "Please enter a number: ";

        cin >> toppingChoice;
        if (toppingChoice == 0) {
            break;
        }

        order.addTopping(toppings[toppingChoice - 1]);

        cout << "You have added " << toppings[toppingChoice - 1].name << " to your pizza. Your current price is: " << fixed << setprecision(2) << order.totalPrice << " credits.\n";

        cout << "Would you like to add additional toppings?\nPlease input 'Y' for yes and 'N' for no: ";
        cin >> addMoreToppings;
    }
}

void PizzaSystem::checkout(Order& order) {
    if (order.totalPrice <= credits) {
        cout << "Checking out...\n";
        cout << "........................................\n";
        cout << "Available Balance:     " << fixed << setprecision(2) << credits << " credits\n";
        cout << "Pizza price:           " << fixed << setprecision(2) << order.totalPrice << " credits\n";
        cout << "----------------------------------------\n";
        double remainingCredits = credits - order.totalPrice;
        cout << "Your new Balance = " << fixed << setprecision(2) << remainingCredits << " credits\n";
        cout << "----------------------------------------\n";

        credits = remainingCredits;
        recentOrders.insert(recentOrders.begin(), order);

        cout << "Thank you for your purchase!\n";
    } else {
        cout << "........................................\n";
        cout << "Available Balance:       " << fixed << setprecision(2) << credits << " credits\n";
        cout << "Pizza price:             " << fixed << setprecision(2) << order.totalPrice << " credits\n";
        cout << "----------------------------------------\n";
        cout << "You have insufficient credits available. You require \"" << fixed << setprecision(2) << order.totalPrice << "\" credits.\n";

        char addMoreCredits;
        cout << "Would you like to add more credits?\nPlease enter 'Y' for yes and 'N' for no: ";
        cin >> addMoreCredits;
        if (addMoreCredits == 'Y' || addMoreCredits == 'y') {
            double additionalCredits;
            cout << "........................................\n";
            cout << "Please enter how many credits you would like to add to your balance: ";
            cin >> additionalCredits;
            credits += additionalCredits;
            cout << "........................................\n";
            cout << "Your new Balance = " << fixed << setprecision(2) << credits << " credits\n";
            cout << "Thank you for your purchase!\n";
        } else {
            cout << "Thank you, goodbye!\n";
        }
    }
}

void PizzaSystem::displayRecentOrders() const {
    cout << "Recent Orders - High first criteria only\n";
    for (const auto& order : recentOrders) {
        cout << "Size: " << order.size << " | Toppings: ";
        for (const auto& topping : order.toppings) {
            cout << topping.name << ", ";
        }
        cout << " | Price: " << fixed << setprecision(2) << order.totalPrice << " credits\n";
    }
}

int main() {
    PizzaSystem pizzaSystem;
    int choice;
    Order currentOrder;

    do {
        pizzaSystem.displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                pizzaSystem.addCredits();
                break;
            case 2:
                pizzaSystem.orderPizza(currentOrder);
                break;
            case 3:
                pizzaSystem.checkout(currentOrder);
                break;
            case 4:
                pizzaSystem.displayRecentOrders();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid number.\n";
        }

    } while (choice != 0);

    return 0;
}
