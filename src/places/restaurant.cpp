#include "../declarations.hpp"

#define RESTAURANT_PIZZA_CENA 10
#define RESTAURANT_KEBAB_CENA 10
#define RESTAURANT_PIEROGI_CENA 10
#define RESTAURANT_SCHABOWY_CENA 10
#define RESTAURANT_ZUPA_CENA 10
#define RESTAURANT_HUNGER_STANDARD 30

void handle_restaurant() {
    while (true) {
        set_console_color(3, 0);
        println("Jesteś w restauracji.");
        set_console_color(7, 0);
        println("Wybierz danie do zamówienia:");
        println("1. Pizza (10$)");
        println("2. Kebab (8$)");
        println("3. Pierogi (12$)");
        println("4. Schabowy (15$)");
        println("5. Zupa (5$)");
        println("6. Wyjście");

        string choice = read("#");
        int item_price = 0;
        int item_hunger_added = RESTAURANT_HUNGER_STANDARD;
        switch (choice[0]) {
            case '1':
                item_price = RESTAURANT_PIZZA_CENA;
                break;
            case '2':
                item_price = RESTAURANT_KEBAB_CENA;
                break;
            case '3':
                item_price = RESTAURANT_PIEROGI_CENA;
                break;
            case '4':
                item_price = RESTAURANT_SCHABOWY_CENA;
                break;
            case '5':
                item_price = RESTAURANT_ZUPA_CENA;
                break;
            case '6':
                return;
            default:
                println("Niepoprawny wybór.");
                return;

            if (item_price == 0) continue;
            
            if (money < item_price) {
                println("Nie masz wystarczająco pieniędzy.");
                return;
            }

            remove_money(item_price);
            hunger = hunger - item_hunger_added;
        }
    }
}