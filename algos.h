#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stdbool.h>

typedef enum {
    ALGO_FIFO,
    ALGO_LRU,
    ALGO_OPT,
    ALGO_CLOCK,
    ALGO_NRU,
    ALGO_LFU,
    ALGO_MFU
} AlgorithmType;

typedef struct {
    int page_id;
    char op;
} Reference;

typedef struct {
    int page_id;       // -1 when empty
    int loaded_at;     // Step when loaded (for FIFO and universal tie-breaking)
    int last_used;     // Step when last accessed (for LRU)
    int freq_count;    // Access count since load (for LFU / MFU)
    bool ref_bit;      // R bit (for Clock / NRU)
    bool mod_bit;      // M bit (for NRU / disk writes)
} Frame;

typedef struct {
    int total_refs;
    int page_faults;
    int evictions;
    int disk_writes;
    int num_frames;
    Frame *final_frames;
} SimulationResult;

SimulationResult run_fifo(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_lru(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_opt(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_clock(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_nru(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_lfu(const Reference *refs, int num_refs, int num_frames, bool verbose);
SimulationResult run_mfu(const Reference *refs, int num_refs, int num_frames, bool verbose);

#endif