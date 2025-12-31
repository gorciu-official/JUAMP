#include "../declarations.hpp"

#define PARK_LODY_CENA 5.00
#define PARK_LODY_PUNKTY 7

extern void handle_park_talking();

void handle_park() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w parku");
        set_console_color(7, 0);
        println("  1 - Zagadaj do kogoś");
        println("  2 - Kup lody");
        println("  3 - Kieruj się do wyjścia");
        string choice = read("> ");
        if (choice == "1") {
            handle_park_talking();
        } else if (choice == "2") {
            if (player->money < PARK_LODY_CENA) {
                println("Nie masz wystarczająco pieniędzy na lody.");
            } else {
                remove_money(PARK_LODY_CENA);
                player->hunger = player->hunger - PARK_LODY_PUNKTY;
                println("Kupiłeś lody.");
            }
        } else if (choice == "3") {
            break;
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}