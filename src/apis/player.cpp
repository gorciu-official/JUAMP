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
    toml::table save_data{
        {"sisters", this->sisters},
        {"brothers", this->brothers},
        {"was_outside_before", this->was_outside_before},
        {"was_talking_before", this->was_talking_before},
        {"has_reputation_before", this->has_reputation_before},
        {"last_talked_with", this->last_talked_with},
        {"mum_tokens", this->mum_tokens},
        {"hunger", this->hunger},
        {"money", this->money},
        {"name", this->name},
        {"city", this->city},
        {"age", this->age},
        {"gender", this->gender},
        {"reputation", this->reputation}
    };

#ifdef _WIN32
    system("if not exist saves mkdir saves");
#else
    system("mkdir -p ~/.local");
    system("mkdir -p ~/.local/state");
    system("mkdir -p ~/.local/state/JUAMP");
    system("mkdir -p ~/.local/state/JUAMP/saves");
#endif

    std::ofstream file(SAVE_FILE);
    if (!file.is_open()) return false;
    file << save_data;
    file.close();
    return true;
}