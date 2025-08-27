#include "../declarations.hpp"
#include "../constants.hpp"

// Newspaper only available in the "Ropucha" shop
extern void handle_newspaper();

// src/talking.cpp
extern void handle_ropucha_talking();

void handle_ropucha() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepiku \"Ropucha!\"");
        set_console_color(7, 0);
        println("  1 - Wyjdź ze sklepu");
        println("  2 - Kup bagietkę");
        println("  3 - Kup gazetę");
        println("  4 - Zagadaj babę w sklepie");

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
            pause_nul();
            continue;
        } else if (readed == "4") {
            handle_ropucha_talking();
            continue;
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
        sleep_seconds(0.5);
    }
}