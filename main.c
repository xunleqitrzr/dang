#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define print(...) printf(__VA_ARGS__)
#define err(...) fprintf(stderr, __VA_ARGS__)

typedef struct {
    char* input_file;
    int   count;
} Config;

void parse_arguments(int argc, char* argv[], Config* cfg) {
    int opt;

    // default values
    cfg->input_file = NULL;
    cfg->count = 1;

    while ((opt = getopt(argc, argv, "i:c:")) != -1) {
        switch (opt) {
            case 'i':
                cfg->input_file = optarg;
                break;

            case 'c':
                cfg->count = atoi(optarg);
                if (cfg->count <= 0) {
                    err("Error: count must be a non-zero and positive number.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case '?':
                exit(EXIT_FAILURE);
                break;

            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    Config cfg;

    parse_arguments(argc, argv, &cfg);

    print("--- Program Configuration ---\n");
    print("Input File: %s\n", cfg.input_file ? cfg.input_file : "None");
    print("Count: %d\n", cfg.count);

    return 0;
}