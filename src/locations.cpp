#include "declarations.hpp"

std::vector<Location> locations = {
    {"plac.main.centered", "Główny plac Nopsanii", "Sam środek placu Nopsanii do którego zjedżają się tłumy ludzi każdego roku. Centrum religijnych wierzeń mieszkańców\nkraju, do którego każdy człowiek odbywa z własnej woli pielgrzymkę. Stoi tu kapłan (`zagadaj kaplan`).", {{"w", "plac.main.west"}, {"e", "plac.main.east"}, {"n", "plac.treninghall"}}},
    {"plac.main.east", "Plac główny", "Poboczna część głównego placu Nopsanii. Nie odgrywa żadnej roli (oprócz drogi do środka).", {{"w", "plac.main.centered"}, {"n", "schronisko"}}},
    {"plac.main.west", "Plac główny", "Poboczna część głównego placu Nopsanii. Nie odgrywa żadnej roli (oprócz drogi do środka).", {{"e", "plac.main.centered"}, {"w", "ropucha"}}},
    {"plac.treninghall", "Hala Ćwiczeniowa", "Miejsce gdzie możesz bezpiecznie ćwiczyć i trenować swoje umiejętności. Stoi tu ochroniarz.", {{"s", "plac.main.centered"}}},
    {"ropucha", "Ropucha", "Najważniejszy sklep w stolicy. To tu można dostać coś do jedzenia oraz można dostać gazetę, która pisze o misjach pobocznych,\nktóre możesz wykonać, aby zdobyć więcej kasy. Stoi tu sprzedawczyni.", {{"e", "plac.main.west"}}},
    {"schronisko", "Schronisko dla zwierząt", "Stoi tu pani, jeśli porozmawiasz, może Ci się udać zdobyć własnego pieska lub kotka.", {{"s", "plac.main.east"}}}
};