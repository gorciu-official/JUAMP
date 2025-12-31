#include "../declarations.hpp"

extern void handle_city_aspergillia();
extern void handle_city_nopsania();

void handle_train_station() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś na dworcu PKP miasta " + player->city);
        set_console_color(7, 0);
        println("  1 - Kup bilet");
        println("  2 - Wyjdź z dworca");
        string choice = read("> ");
        if (choice == "1") {
            if (player->money < 30) {
                println("Nie masz wystarczająco pieniędzy na bilet.");
            } else {
                int city_num = 0;
                remove_money(30);
                while (true) {
                    println("Do jakiego miasta chcesz dojechać?");
                    println("  1 - Aspergillia");
                    println("  2 - Nopsania [stolica]");
                    string city_choice = read("> ");
                    if (city_choice == "1") {
                        println("Kupiłeś bilet do Aspergillii.");
                        city_num = 1;
                        handle_city_aspergillia();
                        println("Wracasz do domu.");
                        break;
                    } else if (city_choice == "2") {
                        println("Kupiłeś bilet do Nopsanii.");
                        city_num = 2;
                        handle_city_nopsania();
                        println("Wracasz do domu.");
                        break;
                    } else {
                        println("Nie ma takiego miasta.");
                        continue;
                    }
                }
                Sleep(10000);
            }
        } else if (choice == "2") {
            break;
        } else {
            println("<Ochrona dworca> Co ty chcesz właściwie zrobić?");
        }
    }
}