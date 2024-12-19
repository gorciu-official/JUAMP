#include "declarations.h"

#define SHOP_ROPUCHA_CENA_BAGIETKA 3.50
#define SHOP_ROPUCHA_PUNKTY_BAGIETKA 16

void handle_ropucha() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepiku \"Ropucha!\"");
        set_console_color(7, 0);
        println("  1 - Wyjdź ze sklepu");
        println("  2 - Kup bagietkę");

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
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}