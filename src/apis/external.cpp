#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include "../declarations.hpp"

int ansi_to_juamp_color(int ansi) {
    switch (ansi) {
        case 30: case 90:  return 0; 
        case 31: case 91:  return 1; 
        case 32: case 92:  return 2;
        case 33: case 93:  return 3;
        case 34: case 94:  return 4;
        case 35: case 95:  return 5;
        case 36: case 96:  return 6;
        case 37: case 97:  return 7; 
    }
    return -1;
}

void print_with_ansi(const char* text) {
    static int fg = 7;
    static int bg = 0;

    const char* p = text;
    std::string chunk;

    while (*p) {
        if (*p == '\x1b' && *(p + 1) == '[') {
            if (!chunk.empty()) {
                print(chunk);
                chunk.clear();
            }

            p += 2;
            int code = 0;

            while (*p && *p != 'm') {
                if (*p >= '0' && *p <= '9')
                    code = code * 10 + (*p - '0');
                p++;
            }

            if (*p == 'm') {
                if (code == 0) {
                    fg = 7;
                    bg = 0;
                } else if (code >= 30 && code <= 37 || code >= 90 && code <= 97) {
                    int c = ansi_to_juamp_color(code);
                    if (c != -1) fg = c;
                } else if (code >= 40 && code <= 47 || code >= 100 && code <= 107) {
                    int c = ansi_to_juamp_color(code - 10);
                    if (c != -1) bg = c;
                }
                set_console_color(fg, bg);
            }
        } else {
            chunk += *p;
        }
        p++;
    }

    if (!chunk.empty())
        print(chunk);
}

int execcmd(const string& cmd) {
    int out_pipe[2];
    int err_pipe[2];

    pipe(out_pipe);
    pipe(err_pipe);

    pid_t pid = fork();
    if (pid == 0) {
        int devnull = open("/dev/null", O_RDONLY);
        dup2(devnull, STDIN_FILENO);
        close(devnull);

        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);

        close(out_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[0]);
        close(err_pipe[1]);

        execl("/bin/sh", "sh", "-c", cmd.c_str(), nullptr);
        _exit(127);
    }

    close(out_pipe[1]);
    close(err_pipe[1]);

    char buffer[512];

    bool out_open = true;
    bool err_open = true;

    while (out_open || err_open) {
        if (out_open) {
            ssize_t n = read(out_pipe[0], buffer, sizeof(buffer) - 1);
            if (n > 0) {
                buffer[n] = 0;
                print_with_ansi(buffer);
            } else {
                out_open = false;
                close(out_pipe[0]);
            }
        }

        if (err_open) {
            ssize_t n = read(err_pipe[0], buffer, sizeof(buffer) - 1);
            if (n > 0) {
                buffer[n] = 0;
                set_console_color(1, 0);
                print(buffer);
                set_console_color(7, 0);
            } else {
                err_open = false;
                close(err_pipe[0]);
            }
        }
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return -1;
}
