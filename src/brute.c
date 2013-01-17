#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>

int brute_force(const char *charset, size_t maxlen, int (*callback)(const char *))
{
    const size_t charset_max = strlen(charset);
    char permutation[maxlen + 1];
    int charset_array[maxlen];

    memset(permutation, 0, sizeof(permutation));
    memset(charset_array, 0, sizeof(charset_array));

    int current_len = 0;
    int current_byte = 0;
    while (current_len < maxlen) {
        for (int i = 0; i <= current_len; i++)
            permutation[i] = charset[charset_array[current_len - i]];

        if (callback(permutation))
            return 0;

        charset_array[current_byte]++;
        while (charset_array[current_byte] == charset_max) {
            charset_array[current_byte] = 0;
            current_byte++;
            if (current_byte > current_len) {
                current_len = current_byte;
                break;
            }
            charset_array[current_byte]++;
        }
        current_byte = 0;
    }

    return 1;
}

int callback(const char *permutation)
{
    // insert magic here:
    puts(permutation);
    return 0;
}

int main(int argc, char **argv)
{
    int maxlen = 8;
    if (argc > 1)
        maxlen = atoi(argv[1]);

    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    if (!brute_force(charset, maxlen, callback)) {
        printf("win!\n");
        return 0;
    }

    return 1;
}
