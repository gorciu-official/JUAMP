#include "declarations.h"
#include <string>
#include <vector>

#define PARK_LODY_CENA 5.00
#define PARK_LODY_PUNKTY 7

void handle_park_talking() {
    std::vector<std::vector<string>> dialogues = {
        {"<Ty> Nic się panu nie stało?", "<Mężczyzna> Nie, nic się nie stało. Co u Ciebie?", "<Ty> Wszystko w porządku. Co pan tu robi?", "<Mężczyzna> Spaceruję sobie. Nudzi mi się. W domu nie mam niczego do roboty. Babka zawsze mnie wypycha na dwór.", "<Ty> Aha. To ja idę dalej. Miłego spaceru.", "<Mężczyzna> Dziękuję."},
        {"<Ty> Dzień dobry, co słychać?", "<Kobieta> Dzień dobry, wszystko dobrze. A u Ciebie?", "<Ty> Też dobrze. Co pani tu robi?", "<Kobieta> Przyszłam na spacer z psem. Lubię spędzać czas na świeżym powietrzu.", "<Ty> To miłego spaceru.", "<Kobieta> Dziękuję, nawzajem."},
        {"<Ty> Cześć, jak się masz?", "<Chłopak> Cześć, dobrze. A Ty?", "<Ty> Też dobrze. Co robisz w parku?", "<Chłopak> Przyszedłem pobiegać. Lubię aktywnie spędzać czas.", "<Ty> To powodzenia w bieganiu.", "<Chłopak> Dzięki, miłego dnia."}
    };

    while (true) {
        int random_index = get_random_number() % dialogues.size();

        printnl();
        set_console_color(7, 0);
        for (const auto& line : dialogues[random_index]) {
            println(line);
            Sleep(500);
        }

        printnl();
        set_console_color(3, 0);
        println("Czy chcesz zagadać do kogoś innego? (T/N)");
        string choice = read("> ", 0xD);
        if (choice != "T") {
            break;
        }

        println("Idziesz dalej. Szukasz osoby, która chciałaby porozmawiać.");
        Sleep(3000);
        continue;
    }
}

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
            if (money < PARK_LODY_CENA) {
                println("Nie masz wystarczająco pieniędzy na lody.");
            } else {
                remove_money(PARK_LODY_CENA);
                hunger = hunger - PARK_LODY_PUNKTY;
                println("Kupiłeś lody.");
            }
        } else if (choice == "3") {
            break;
        } else {
            println("Niepoprawny numer/znak");
        }
    }
}