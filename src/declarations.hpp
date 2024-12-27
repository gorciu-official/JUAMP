#pragma once

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define Sleep(ms) sleep((ms) / 1000)
#endif
#ifdef _WIN32
#include <windows.h>
#endif

#define sleep_seconds(ms) Sleep(ms * 1000)

#include <iostream>

typedef std::string string;

extern int sisters;
extern int brothers;
extern bool was_outside_before;
extern bool was_talking_before;
extern string last_talked_with;
extern int mum_tokens;
extern int hunger;
extern int money;
extern string name;
extern string city;
extern int age;
extern int sex;

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