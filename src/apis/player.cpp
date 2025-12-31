#include "../declarations.hpp"
#include "../toml.hpp"

extern string SAVE_FILE;

Player::Player()
    : sisters(0),
      brothers(0),
      was_outside_before(false),
      was_talking_before(false),
      has_reputation_before(false),
      last_talked_with("Mama"),
      mum_tokens(0),
      hunger(0),
      money(1000),
      name(""),
      city(""),
      age(12),
      gender(2),
      reputation(100)
{}

bool Player::save_player_data() {
    return true;
    toml::table save_data {
        {"sisters", sisters},
        {"brothers", brothers},
        {"was_outside_before", was_outside_before},
        {"was_talking_before", was_talking_before},
        {"has_reputation_before", has_reputation_before},
        {"last_talked_with", last_talked_with},
        {"mum_tokens", mum_tokens},
        {"hunger", hunger},
        {"money", money},
        {"name", name},
        {"city", city},
        {"age", age},
        {"gender", gender},
        {"reputation", reputation}
    };

#ifdef _WIN32
    system("if not exist saves mkdir saves");
#else
    system("mkdir -p ~/.local");
    system("mkdir -p ~/.local/state");
    system("mkdir -p ~/.local/state/JUAMP");
    system("mkdir -p ~/.local/state/JUAMP/saves");
#endif

    std::ofstream file(SAVE_FILE, std::ios::trunc);
    if (!file.is_open())
        return false;

    file << save_data;
    file.flush();

    return file.good();
}