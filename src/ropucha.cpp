#include "declarations.h"

// Newspaper only available in the "Ropucha" shop
extern void handle_newspaper();

#define SHOP_ROPUCHA_CENA_BAGIETKA 3.50
#define SHOP_ROPUCHA_PUNKTY_BAGIETKA 16

#define SHOP_ROPUCHA_CENA_GAZETA 1.50

void handle_ropucha() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepiku \"Ropucha!\"");
        set_console_color(7, 0);
        println("  1 - Wyjdź ze sklepu");
        println("  2 - Kup bagietkę");
        println("  3 - Kup gazetę");

        string readed = read("> ", 2);
        if (readed == "1") {
            return;
        } else if (readed == "2") {
            if (SHOP_ROPUCHA_CENA_BAGIETKA > money) {
                set_console_color(4, 0);
                println("Niestety nie stać cię na taki wydatek!");
                set_console_color(7, 0);
                continue;
            }
            remove_money(SHOP_ROPUCHA_CENA_BAGIETKA);
            hunger = hunger - SHOP_ROPUCHA_PUNKTY_BAGIETKA;
            continue;
        } else if (readed == "3") {
            if (SHOP_ROPUCHA_CENA_GAZETA > money) {
                set_console_color(4, 0);
                println("Niestety nie stać cię na taki wydatek!");
                set_console_color(7, 0);
                continue;
            }
            remove_money(SHOP_ROPUCHA_CENA_GAZETA);
            handle_newspaper();
            continue;
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}