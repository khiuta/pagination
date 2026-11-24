#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "algos.h"

typedef enum{
  ALGO = 2,
  FRAMES = 4,
  TRACE = 6,
  VERBOSE = 7
} Args;

Reference *load_trace(const char *filepath, int *out_count) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("Failed to open trace file");
        exit(EXIT_FAILURE);
    }

    int capacity = 64;
    int count = 0;
    Reference *refs = malloc(capacity * sizeof(Reference));
    if (!refs) {
        perror("malloc failed");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        while (isspace((unsigned char)*p)) p++;

        // Skip blank lines and comments
        if (*p == '\0' || *p == '#') continue;

        int page;
        char op = 'R';
        if (sscanf(p, "%d %c", &page, &op) >= 1) {
            // Grow array if full
            if (count == capacity) {
                capacity *= 2;
                Reference *temp = realloc(refs, capacity * sizeof(Reference));
                if (!temp) {
                    perror("realloc failed");
                    free(refs);
                    fclose(fp);
                    exit(EXIT_FAILURE);
                }
                refs = temp;
            }

            refs[count].page_id = page;
            refs[count].op = (char)toupper((unsigned char)op);
            count++;
        }
    }

    fclose(fp);
    *out_count = count; // Pass total number of parsed references back to caller
    return refs;
}

SimulationResult run_algo(char* algorithm, Reference* refs, int num_refs, int num_frames, bool verbose){
  SimulationResult results;
  if(strcmp(algorithm, "FIFO") == 0 || strcmp(algorithm, "fifo") == 0) results = run_fifo(refs, num_refs, num_frames, verbose);
  else if(strcmp(algorithm, "LRU") == 0 || strcmp(algorithm, "lru") == 0) results = run_lru(refs, num_refs, num_frames, verbose);

  return results;
}

void parse_results(SimulationResult results, char* algorithm, int num_frames, int total_refs){
  printf("Algoritmo: %s\n", algorithm);
  printf("Frames: %i\n", results.num_frames);
  printf("Referências: %i\n", total_refs);
  printf("Falta de páginas: %i\n", results.page_faults);
  printf("Taxa de faltas: %.2f%\n", (float)total_refs / (float)results.page_faults);
  printf("Evicções: %i\n", results.evictions);
  printf("Escritas em disco: %i\n", results.disk_writes);
  printf("Conjunto residente final:\n");

  printf("frame_ids:    ");
  for(int i = 0; i < num_frames; i++){ printf("%i    ", i); }
  printf("\n");
  printf("page_ids:     ");
  for(int i = 0; i < num_frames; i++){ printf("%i    ", results.final_frames[i].page_id); }
  printf("\n");
}

int main(int argc, char* argv[]){
  char* algo_name = NULL;
  int frames = 0;
  char* trace_path = NULL;
  bool verbose = false;
  if(argc >= 7 && argc < 9){
    algo_name = argv[ALGO];
    frames = atoi(argv[FRAMES]);
    trace_path = argv[TRACE];
    if(argc == 8) verbose = argv[VERBOSE];
  } else if(argc >= 9) {
    printf("Error: Too many arguments.");
  } else{
    printf("Error: Not enough arguments.");
  }

  int total_refs = 0;
  int* total = &total_refs;
  Reference* refs = load_trace(trace_path, total);

  SimulationResult results = run_algo(algo_name, refs, total_refs, frames, verbose);
  parse_results(results, algo_name, frames, total_refs);

  return 0;
}