#include "../declarations.hpp"

void add_one_hunger() {
    player->hunger++;
    if (player->hunger == 75) {
        print_message_box("Uwaga!", "Jesteś głodny! Może czas pójść na halę targową i kupić coś do jedzenia.");
    }
    if (player->hunger == 90) {
        print_message_box("OSTATNIE OSTRZEŻENIE!", "Jesteś naprawdę głodny. Musisz kupić coś do jedzenia. Jeżeli nie zareagujesz na to ostrzeżenie, Twoja rozgrywka może się bezpowrotnie skończyć.");
    }
    if (player->hunger > 115) {
        print_message_box("Rozgrywka zakończona!", "Zignorowałeś ostrzeżenia dotyczące głodu twojej postaci. Nie jesteś w stanie kontynuować rozgrywki.");
        while (true) {
            continue;
        }
    }
}