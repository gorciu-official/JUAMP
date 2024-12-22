#include "declarations.h"

void handle_nopsania() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w Nopsanii");
        set_console_color(7, 0);
        println("  1 - Idź na dworzec PKP");
        println("  2 - Idź do parku");
        println("  3 - Idź do sklepu");
        println("  4 - Idź do restauracji");
        println("  5 - Idź do kina");
        string choice = read("> ");
        if (choice == "1") {
            break;
        } else if (choice == "2") {
            println("Zostanie dodane w następnej aktualizacji.");
        } else if (choice == "3") {
            handle_nopsania_shop();
        } else if (choice == "4") {
            println("Zostanie dodane w następnej aktualizacji.");
        } else if (choice == "5") {
            println("Zostanie dodane w następnej aktualizacji.");
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}

#define NOPSANIA_SHOP_KAWA_CENA 12.00
#define NOPSANIA_SHOP_KAWA_PUNKTY 8
#define NOPSANIA_SHOP_WODA_CENA 7.00
#define NOPSANIA_SHOP_WODA_PUNKTY 12

void handle_nopsania_shop() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepie w Nopsanii");
        set_console_color(7, 0);
        println("  1 - Kup kawę");
        println("  2 - Kup herbatę");
        println("  3 - Kup wodę");
        println("  4 - Wyjdź ze sklepu");
        string choice = read("> ");
        if (choice == "1") {
            if (money < NOPSANIA_SHOP_KAWA_CENA) {
                println("Nie masz wystarczająco pieniędzy na kawę.");
            } else {
                remove_money(NOPSANIA_SHOP_KAWA_CENA);
                hunger = hunger - NOPSANIA_SHOP_KAWA_PUNKTY;
                println("Kupiłeś kawę.");
            }
        } else if (choice == "2") {
            println("Zostanie dodane w następnej aktualizacji.");
        } else if (choice == "3") {
           if (money < NOPSANIA_SHOP_WODA_CENA) {
                println("Nie masz wystarczająco pieniędzy na wodę.");
            } else {
                remove_money(NOPSANIA_SHOP_WODA_CENA);
                hunger = hunger - NOPSANIA_SHOP_WODA_PUNKTY;
                println("Kupiłeś wodę.");
            }
        } else if (choice == "4") {
            break;
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}