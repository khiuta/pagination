#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum{
  ALGO = 2,
  FRAMES = 4,
  TRACE = 6,
  VERBOSE = 7
} Args;

void load_trace(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("Error opening trace file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Trim leading whitespace
        char *p = line;
        while (isspace((unsigned char)*p)) p++;

        // Ignore blank lines and comments
        if (*p == '\0' || *p == '#') continue;

        int page;
        char op = 'R'; // Default to Read
        // sscanf reads the integer and optionally a trailing character
        if (sscanf(p, "%d %c", &page, &op) >= 1) {
            op = toupper((unsigned char)op);
            // Store (page, op) in your array/vector here
        }
    }
    fclose(fp);
}

int main(int argc, char* argv[]){
  if(argc >= 7 && argc < 9){
    printf("Arguments: %s\n", argv[ALGO]);
    printf("Arguments: %s\n", argv[FRAMES]);
    printf("Arguments: %s\n", argv[TRACE]);
    if(argc == 8) printf("Arguments: %s", argv[VERBOSE]);
  } else if(argc >= 9) {
    printf("Error: Too many arguments.");
  } else{
    printf("Error: Not enough arguments.");
  }

  return 0;
}