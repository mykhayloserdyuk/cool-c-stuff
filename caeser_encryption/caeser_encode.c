#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt() {
    char text[10000], ch;
    int key;
    scanf("%d", &key);


    // Taking text as input.
    FILE *fPtr = fopen("text.txt", "r");
    if (fPtr == NULL) {
        printf("Error opening file.");
        return;
    }
    
    int i = 0;
    while (fgets(text + i, sizeof(text) - i, fPtr) != NULL) {
        i = strlen(text);
        if (text[i - 1] == '\n') {
            text[i - 1] = '\0'; // Remove newline character
            break;
        }
    }
    
    fclose(fPtr);

    // Visiting character by character.
    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        // Check for valid characters.
        if (isalnum(ch)) {
            // Lowercase characters.
            if (islower(ch)) {
                ch = (ch - 'a' + key) % 26 + 'a';
            }
            // Uppercase characters.
            if (isupper(ch)) {
                ch = (ch - 'A' + key) % 26 + 'A';
            }
            // Numbers.
            if (isdigit(ch)) {
                ch = (ch - '0' + key) % 10 + '0';
            }
        }
        // Invalid character.
        else {
            printf("Invalid Message");
        }
        // Adding encoded answer.
        text[i] = ch;
    }

    FILE *fptr;
    fptr = fopen("encrypted.txt", "w");
    fprintf(fptr, "%s", text);
    fclose(fptr);
}

int main(void) {
    encrypt();
    return 0;
}
