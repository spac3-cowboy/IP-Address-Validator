#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool validateIPv4Part(const char *part) {
    int num = atoi(part);
    return (num >= 0 && num <= 255 && part[0] != '0' && atoi(part) == num);
    // Validates if the part is a valid IPv4 part:
    // - Checks if it is in the range of 0 to 255 (inclusive)
    // - Ensures that the part does not have leading zeros
    // - Compares the converted integer value with the original string to handle leading zeros properly
}

bool validateIPv4(const char *ipStr) {
    int dots = 0;
    const char *ptr = ipStr;

    while (*ptr) {
        const char *nextDot = strchr(ptr, '.');
        const char *partEnd = (nextDot == NULL) ? ptr + strlen(ptr) : nextDot;

        if (!validateIPv4Part(ptr) || ptr == partEnd)
            return false;
        // If the part is not a valid IPv4 part or the loop has reached the end of the string without encountering a valid part, return false

        if (nextDot != NULL)
            dots++;

        ptr = partEnd + 1;
    }

    return dots == 3;
    // Returns true if there are exactly 3 dots (indicating 4 parts)
}

bool validateIPv6Part(const char *part) {
    size_t len = strlen(part);
    if (len > 4)
        return false;
    // If the part has more than 4 characters, it is invalid

    for (size_t i = 0; i < len; i++) {
        char c = part[i];
        if (!isxdigit(c))
            return false;
        // If any character is not a valid hexadecimal digit, return false
    }

    return true;
    // All characters are valid hexadecimal digits, so return true
}

bool validateIPv6(const char *ipStr) {
    int colons = 0;
    const char *ptr = ipStr;

    while (*ptr) {
        const char *nextColon = strchr(ptr, ':');
        const char *partEnd = (nextColon == NULL) ? ptr + strlen(ptr) : nextColon;

        if (!validateIPv6Part(ptr) || ptr == partEnd)
            return false;
        // If the part is not a valid IPv6 part or the loop has reached the end of the string without encountering a valid part, return false

        if (nextColon != NULL)
            colons++;

        ptr = partEnd + 1;
    }

    return colons >= 2 && colons <= 7;
    // Returns true if there are between 2 and 7 colons (indicating 3 to 8 parts)
}

int main() {
    char ipStr[40];

    printf("Enter an IP address: ");
    fgets(ipStr, sizeof(ipStr), stdin);
    ipStr[strcspn(ipStr, "\n")] = '\0';
    // Read input from the user and remove the trailing newline character

    if (validateIPv4(ipStr))
        printf("Valid IPv4 address: %s\n", ipStr);
    else if (validateIPv6(ipStr))
        printf("Valid IPv6 address: %s\n", ipStr);
    else
        printf("Invalid IP address: %s\n", ipStr);
    // Validate the input and print the appropriate message

    return 0;
}
