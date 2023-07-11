#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int validateIPv4Part(const char *part) {
    // Check if part contains only digits
    for (size_t i = 0; i < strlen(part); i++) {
        if (!isdigit(part[i])) {
            return 0;
        }
    }

    // Check if part is not longer than 3 digits
    if (strlen(part) > 3) {
        return 0;
    }

    // Check if part has leading zeros
    if (strlen(part) > 1 && part[0] == '0') {
        return 0;
    }

    // Convert part to integer and check if it is within the valid range
    int num = atoi(part);
    if (num < 0 || num > 255) {
        return 0;
    }

    return 1;
}

int validateIPv4(const char *ipStr) {
    int dots = 0;
    const char *ptr = ipStr;

    // Check if each part of the IPv4 address is valid
    while (*ptr) {
        const char *nextDot = strchr(ptr, '.');
        const char *partEnd = (nextDot == NULL) ? ptr + strlen(ptr) : nextDot;

        size_t partLen = partEnd - ptr;
        char part[partLen + 1];
        strncpy(part, ptr, partLen);
        part[partLen] = '\0';

        if (!validateIPv4Part(part) || ptr == partEnd) {
            return 0;
        }

        if (nextDot != NULL) {
            dots++;
        }

        ptr = partEnd + 1; // Move to the next part
    }

    // Check if the IPv4 address contains exactly 3 dots
    if (dots != 3) {
        return 0;
    }

    return 1;
}

int validateIPv6Part(const char *part) {
    // Check if part is a valid hexadecimal number
    for (size_t i = 0; i < strlen(part); i++) {
        if (!isxdigit(part[i])) {
            return 0;
        }
    }

    // Check if part is not longer than 4 digits
    if (strlen(part) > 4) {
        return 0;
    }

    return 1;
}

int validateIPv6(const char *ipStr) {
    int colons = 0;
    const char *ptr = ipStr;

    // Check if each part of the IPv6 address is valid
    while (*ptr) {
        const char *nextColon = strchr(ptr, ':');
        const char *partEnd = (nextColon == NULL) ? ptr + strlen(ptr) : nextColon;

        size_t partLen = partEnd - ptr;
        char part[partLen + 1];
        strncpy(part, ptr, partLen);
        part[partLen] = '\0';

        if (!validateIPv6Part(part) || ptr == partEnd) {
            return 0;
        }

        if (nextColon != NULL) {
            colons++;
        }

        ptr = partEnd + 1; // Move to the next part
    }

    // Check if the IPv6 address contains between 2 and 7 colons
    if (colons < 2 || colons > 7) {
        return 0;
    }

    return 1;
}

int main() {
    char ipStr[40];

    printf("Enter an IP address: ");
    scanf("%39s", ipStr);

    if (validateIPv4(ipStr)) {
        printf("Valid IPv4 address: %s\n", ipStr);
    } else if (validateIPv6(ipStr)) {
        printf("Valid IPv6 address: %s\n", ipStr);
    } else {
        printf("Invalid IP address: %s\n", ipStr);
    }

    return 0;
}
