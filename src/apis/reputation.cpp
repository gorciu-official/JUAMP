#include "declarations.hpp"

void add_reputation(int what) {
    if (!has_reputation_before) {
        int cfg = current_foreground;
        int cbg = current_background;
        set_console_color(2, 0);
        println("Właśnie zdobyłeś pierwsze punkty reputacji. Reputacja bezpośrednio odbija się na zachowanie");
        println("bohaterów gry, zwłaszcza krytycznej rodziny. Jeżeli masz niską reputację, istnieje nawet szansa,");
        println("że szef w pracy odmówi zatrudnienia Ciebie. Dbaj o reputację jak o własne życie.");
        set_console_color(cfg, cbg);
        has_reputation_before = true;
    }
    reputation += what;
}

void remove_reputation(int what) {
    reputation -= what;
}