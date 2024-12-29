#include "declarations.hpp"

void handle_casino() {
    while (true) {
        set_console_color(7, 0);
        println("Co chcesz robić? Automaty (S), Ruletka (R), Gry karciane (C), czy wyjść (E)?");
        string response = read("# ", 0x0D);

        if (response[0] == 'E' || response[0] == 'e') {
            println("<Miły pan> Żegnam Cię, szczęścia w przyszłości!");
            break;
        }

        println("Ile chcesz obstawić? Podaj kwotę (minimum 50$):");
        int bet_amount;
        try {
            bet_amount = stoi(read("# ", 0x0D));
        } catch (const std::invalid_argument& e) {
            set_console_color(4, 0);
            println("Nieprawidłowa kwota. Spróbuj ponownie.");
            set_console_color(7, 0);
            continue;
        }
        if (bet_amount < 50) {
            set_console_color(4, 0);
            println("Minimalna stawka to 50$. Spróbuj ponownie.");
            set_console_color(7, 0);
            continue;
        }
        if (money < bet_amount) {
            set_console_color(4, 0);
            println("Ostrzeżenie: zadłużasz się. Może czas przestać grać?");
            set_console_color(7, 0);
        }

        if (response[0] == 'S' || response[0] == 's') {
            // Gra na automatach
            println("Grasz na automatach za " + std::to_string(bet_amount) + "$.");
            int slot1 = get_random_number() % 5;
            int slot2 = get_random_number() % 5;
            int slot3 = get_random_number() % 5;

            println(std::to_string(slot1) + " " + std::to_string(slot2) + " " + std::to_string(slot3));

            if (slot1 == slot2 && slot2 == slot3) {
                set_console_color(0x0D, 0);
                println("Jackpot! Wygrywasz " + std::to_string(bet_amount * 10) + "$!");
                set_console_color(7, 0);
                add_money(bet_amount * 10);
            } else if (slot1 == slot2 || slot1 == slot3 || slot2 == slot3) {
                set_console_color(0x0D, 0);
                println("Wygrałeś " + std::to_string(bet_amount * 2) + "$!");
                set_console_color(7, 0);
                add_money(bet_amount * 2);
            } else {
                set_console_color(4, 0);
                println("Przegrałeś " + std::to_string(bet_amount) + "$.");
                set_console_color(7, 0);
                remove_money(bet_amount);
            }
        } else if (response[0] == 'R' || response[0] == 'r') {
            println("Obstawiasz " + std::to_string(bet_amount) + "$. Czerwone (R) czy czarne (B)?");
            string bet = read("# ", 0x0D);

            println("Ruletka się kręci...");
            sleep_seconds(1);

            int random_num = get_random_number() % 2;

            if ((bet[0] == 'R' || bet[0] == 'r') && random_num == 0) {
                println("Wygrałeś! Czerwone trafiło!");
                add_money(bet_amount);
            } else if ((bet[0] == 'B' || bet[0] == 'b') && random_num == 1) {
                println("Wygrałeś! Czarne trafiło!");
                add_money(bet_amount);
            } else {
                println("Przegrałeś. Spróbuj jeszcze raz.");
                remove_money(bet_amount);
            }
        } else if (response[0] == 'C' || response[0] == 'c') {
            println("Grasz w oczko za " + std::to_string(bet_amount) + "$.");
            int player_card = (get_random_number() % 10) + 1;
            int dealer_card = (get_random_number() % 10) + 1;

            println("Twoja karta: " + std::to_string(player_card));
            println("Karta krupiera: " + std::to_string(dealer_card));

            if (player_card > dealer_card) {
                println("Wygrałeś! Otrzymujesz " + std::to_string(bet_amount * 2) + "$!");
                add_money(bet_amount * 2);
            } else if (player_card < dealer_card) {
                println("Przegrałeś. Tracisz " + std::to_string(bet_amount) + "$.");
                remove_money(bet_amount);
            } else {
                println("Remis. Nic nie tracisz.");
            }
        } else {
            println("<Miły pan> Nie rozumiem. Spróbuj ponownie.");
        }
    }
}

void handle_work() {
    set_console_color(7, 0);
    
    while (true) {
        println("Wybierz pracę: Bank (B), Fabryka (F), KFC (K), McDonald's (M), czy wyjść (E)?");
        string job_response = read("# ", 0x0D);

        if (job_response[0] == 'E' || job_response[0] == 'e') {
            set_console_color(4, 0);
            println("Przerwałeś pracę.");
            set_console_color(7, 0);
            break;
        }

        int hunger_increase = 0;
        int earnings = 0;
        int time_spent = 0;

        if (job_response[0] == 'B' || job_response[0] == 'b') {
            println("Pracujesz w banku. Siedzisz przy biurku i obsługujesz niezadowolonych klientów.");
            earnings = 2000;
            time_spent = 5;
            hunger_increase = 2;
            sleep_seconds(time_spent / sex);
        } else if (job_response[0] == 'F' || job_response[0] == 'f') {
            println("Pracujesz w fabryce. To ciężka praca przy taśmie produkcyjnej.");
            earnings = 1500;
            time_spent = 7; 
            hunger_increase = 4;
            sleep_seconds(time_spent / sex);
        } else if (job_response[0] == 'K' || job_response[0] == 'k') {
            println("Pracujesz w KFC. Smażysz kurczaki i obsługujesz klientów.");
            earnings = 1000;
            time_spent = 4; 
            hunger_increase = 3;
            sleep_seconds(time_spent / sex);
        } else if (job_response[0] == 'M' || job_response[0] == 'm') {
            println("Pracujesz w McDonald's. Przygotowujesz burgery i obsługujesz klientów.");
            earnings = 1200;
            time_spent = 6;
            hunger_increase = 5;
            sleep_seconds(time_spent / sex);
        } else {
            set_console_color(4, 0);
            println("Wybierz poprawną pracę.");
            set_console_color(7, 0);
            continue;
        }

        println("<Szef> No, wystarczy!");

        for (int i = 0; i < hunger_increase; i++) {
            add_one_hunger();
        }
        add_money(earnings);
    }
}