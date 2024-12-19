#include "declarations.h"

void handle_casino() {
    set_console_color(7, 0);
    println("<Ochrona> Siema mordko! Witaj w tym kasynowskim świecie!");
    
    while (true) {
        println("<Miły pan> Co tam chcesz obstawiać? Czerwone (R) czy czarne (B), a może wyjść chcesz (E)?");
        string response = read("# ");
        
        if (response[0] == 'E' || response[0] == 'e') {
            println("<Miły pan> Żegnam Cię, szczęścia w przyszłości!");
            break;
        }
        
        println("Obstawiasz 250$.");
        int random_num = get_random_int_to_percent() % 2;
        
        if ((response[0] == 'R' || response[0] == 'r') && random_num == 0) {
            println("Wygrałeś! Czerwone trafiło!");
            add_money(250);
        } else if ((response[0] == 'B' || response[0] == 'b') && random_num == 1) {
            println("Wygrałeś! Czarne trafiło!");
            add_money(250);
        } else {
            println("Przegrałeś. Spróbuj jeszcze raz.");
            remove_money(250);
        }
    }
}

void handle_work() {
    set_console_color(7, 0);
    println("<Szef> Witam! Popracujesz se dzisiaj mocno!");
    for (size_t i = 0; i < 30; i++)
    {
        add_one_hunger();
        Sleep(500);
    }
    println("<Szef> No, wystarczy! Możesz iść!");
}