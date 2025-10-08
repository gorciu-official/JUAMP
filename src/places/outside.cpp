#include "../declarations.hpp"

void handle_outside() {
    if (!was_outside_before) {
        printnl();
        set_console_color(2, 0);
        print_center_line("Witaj na zewnątrz! Stąd możesz dostać się do każdego miejsca, jednak są to tylko podstawowe miejsca.");
        print_center_line("Do reszty możesz dostać się tylko poprzez ulice.");
        was_outside_before = true;
    }
    while (true) {
        if (age < 14) check_school_penalty();

        printnl();

        if (get_random_number() % 6 == 3) {
            talk("Bezdomny", "Dasz mi 5 dolarów na chleb?");
            println("Możesz zaakceptować ofertę pisząc T, lub odrzucić pisząc cokolwiek innego.");
            string readed = read("> ", 2);
            if (readed == "t" || readed == "T") {
                remove_money(5);
                add_reputation(1);
                talk("Bezdomny", "Dzięki!");
            }

            continue;
        }

        set_console_color(3, 0);
        println("Jesteś na dworze!");
        set_console_color(7, 0);
        println("  1 - Wróć do domu");
        println("  2 - Odwiedź sklepik \"Ropucha\"");
        println("  3 - Idź na halę targową");
        println("  4 - Idź do kasyna");
        println("  5 - Idź na dworzec ");
        println(std::string("  6 - Idź do szkoły") + (age > 14 ? " [zablokowane]" : ""));

        string readed = read("> ", 2);
        if (readed == "1") {
            return;
        } else if (readed == "2") {
            handle_ropucha();
            continue;
        } else if (readed == "3") {
            handle_market_hall();
            continue;
        } else if (readed == "4") {
            handle_casino();
            continue;
        } else if (readed == "5") {
            handle_train_station();
            continue;
        } else if (readed == "6") {
            if (age < 14) {
                handle_school();
            } else {
                set_console_color(4, 0);
                println("Nie musisz iść do szkoły, bo masz więcej niż 14 lat.");
                set_console_color(7, 0);
            }
            continue;
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}