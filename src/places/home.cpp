#include "../declarations.hpp"

extern void handle_outside();

void handle_home() {
    clear_screen();
    while (true) {
        printnl();

        if (money < 0) {
            set_console_color(7, 0);
            talk("Mama", "JAK ŚMIAŁEŚ SIĘ ZADŁUŻYĆ? TO POWAŻNY PROBLEM DLA NASZEJ RODZINY! WSTYD NA CAŁĄ MIEJSCOWOŚĆ!\nRozumiem że mamy tu wiele fajnych rzeczy, ale nie możemy sobie na nie pozwolić tak często. Lepiej zarabiać\n pieniądze, a nie wydawać je na głupoty! Wynocha do pracy!");
            remove_reputation(3);
            handle_work();
            continue;
        }

        if (money < 30) {
            set_console_color(7, 0);
            talk("Tata", "Mama będzie miała dość spory problem, jeżeli nie zarobisz pieniędzy. Musisz coś zrobić, aby zarobić pieniądze.\nWiesz jak mama potrafi się zdenerwować, kiedy nie masz pieniędzy.\n Lepiej zacznij działać, zanim będzie za późno. Ubierz się i idź do pracy.");
            Sleep(3000);
            handle_work();
            continue;
        }

        set_console_color(3, 0);
        println("Jesteś w domu!");
        set_console_color(7, 0);
        println("  1 - Wyjdź na zewnątrz");
        println("  2 - Zagadaj do kogoś");
        println("  E - Wyjdź z gry");

        string readed = read("> ", 2);
        if (readed == "1") {
            handle_outside();
        } else if (readed == "2") {
            handle_home_talking();
        } else if (readed == "E") {
            return;
        } else {
            set_console_color(4, 0);
            println("Niepoprawny numer/znak");
            set_console_color(7, 0);
        }
    }
}