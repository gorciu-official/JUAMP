#include "../declarations.hpp"

extern void handle_cinema();
extern void handle_restaurant();

#define ASPERGILIA_SHOP_KAWA_CENA 5.00
#define ASPERGILIA_SHOP_KAWA_PUNKTY 7
#define ASPERGILIA_SHOP_HERBATA_CENA 5.00
#define ASPERGILIA_SHOP_HERBATA_PUNKTY 7
#define ASPERGILIA_SHOP_WODA_CENA 1.00
#define ASPERGILIA_SHOP_WODA_PUNKTY 10

void handle_aspergilia_shop() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepie w Aspergillii");
        set_console_color(7, 0);
        println("  1 - Kup kawę");
        println("  2 - Kup herbatę");
        println("  3 - Kup wodę");
        println("  4 - Wyjdź ze sklepu");
        string choice = read("> ");
        if (choice == "1") {
            if (money < ASPERGILIA_SHOP_KAWA_CENA) {
                println("Nie masz wystarczająco pieniędzy na kawę.");
            } else {
                remove_money(ASPERGILIA_SHOP_KAWA_CENA);
                hunger = hunger - ASPERGILIA_SHOP_KAWA_PUNKTY;
                println("Kupiłeś kawę.");
            }
        } else if (choice == "2") {
            if (money < ASPERGILIA_SHOP_HERBATA_CENA) {
                println("Nie masz wystarczająco pieniędzy na herbatę.");
            } else {
                remove_money(ASPERGILIA_SHOP_HERBATA_CENA);
                hunger = hunger - ASPERGILIA_SHOP_HERBATA_PUNKTY;
                println("Kupiłeś herbatę.");
            }
        } else if (choice == "3") {
            if (money < ASPERGILIA_SHOP_WODA_CENA) {
                println("Nie masz wystarczająco pieniędzy na wodę.");
            } else {
                remove_money(ASPERGILIA_SHOP_WODA_CENA);
                hunger = hunger - ASPERGILIA_SHOP_WODA_PUNKTY;
                println("Kupiłeś wodę.");
            }
        } else if (choice == "4") {
            break;
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}

void handle_city_aspergillia() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w Aspergillii");
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
            handle_park();
        } else if (choice == "3") {
            handle_aspergilia_shop();
        } else if (choice == "4") {
            handle_restaurant();
        } else if (choice == "5") {
            handle_cinema();
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}