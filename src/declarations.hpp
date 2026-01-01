#pragma once

// === OS-dependent includes ===

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define Sleep(ms) sleep((ms) / 1000)
#endif
#ifdef _WIN32
#include <windows.h>
#endif

#define sleep_seconds(ms) Sleep(ms * 1000)

// === OS-independent includes ===

#include <iostream>
#include <string>

// === types ===

using std::string;

// === classes ===

class Player {
public:
    Player();
    bool save_player_data();
    int sisters;
    int brothers;
    bool was_outside_before;
    bool was_talking_before;
    bool has_reputation_before;
    string last_talked_with;
    int mum_tokens;
    int hunger;
    int money;
    string name;
    string city;
    int age;
    int gender;
    int reputation;
};

// === save data ===

extern Player* player;

// === unsorted ===

extern int get_random_number();
extern void set_console_color(int foreground, int background);
extern void print(const string& text);
extern void println(const string& text);
extern void printnl();
extern string read(const string prefix, int rfg = 7, int rbg = 0);

extern void remove_money(double money2);
extern void add_money(double money2);
extern void add_one_hunger();

extern void handle_park();

extern void clear_screen();
extern void pause_nul();

extern void talk(string who, string what);

extern void remove_reputation(int what);
extern void add_reputation(int what);

extern string read(const string prefix, int rfg, int rbg);
extern void clear_screen();
extern void talk(string who, string what);
extern void print_center_line(string what, const char placeholder = ' ');
extern int print_message_box(const string& title, const string& desc);

extern void make_directory(std::string dirname);

extern int current_foreground;
extern int current_background;

extern void handle_ropucha();
extern void handle_market_hall();
extern void handle_casino();
extern void handle_work();
extern void handle_train_station();
extern void handle_home_talking();
extern void switch_to_utf8();

extern int execcmd(const string& cmd);