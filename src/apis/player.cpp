#include "../declarations.hpp"

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