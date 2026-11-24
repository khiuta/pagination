#include "algos.h"
#include "helpers.c"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

static Frame *init_frames(int num_frames) {
    // Allocate and initialize empty frames
    Frame* frames = malloc(num_frames * sizeof(Frame));

    for(int i = 0; i < num_frames; i++){ 
      frames[i].page_id = -1;
      frames[i].loaded_at = 0;
      frames[i].last_used = 0;
      frames[i].freq_count = 0;
      frames[i].ref_bit = 0;
      frames[i].mod_bit = 0;
    }

    return frames;
}

static int find_page(const Frame *frames, int num_frames, int page_id) {
    for(int i = 0; i < num_frames; i++){
      if(frames[i].page_id == page_id) return i;
    }

    return -1;
}

static int find_free_frame(const Frame *frames, int num_frames) {
    for(int i = 0; i < num_frames; i++){
      if(frames[i].page_id == -1) return i;
    }

    return -1;
}

SimulationResult run_fifo(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    int i = 0;
    Frame* frames = init_frames(num_frames);
    SimulationResult* results = malloc(sizeof(SimulationResult));
    Queue q;
    initializeQueue(&q);

    while(refs[i].page_id){
      results->total_refs++;

      int frame_page = find_page(frames, num_frames, refs[i].page_id);
      // if the page isnt in any on the frames, there is a page fault
      if(frame_page == -1){
        results->page_faults++;

        int free_frame = find_free_frame(frames, num_frames);
        // if there is no free frame, a page is evicted following the algorithm rule
        if(free_frame == -1){
          dequeue(&q);
          enqueue(&q, refs[i].page_id);
          // put referenced page in new free frame
          free_frame = find_free_frame(frames, num_frames);
          frames[free_frame].page_id = refs[i].page_id;

          
        }
      } else {

      }
    }
}

SimulationResult run_lru(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // LRU implementation
}

SimulationResult run_opt(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // Optimal implementation
}

SimulationResult run_clock(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // Second Chance / Clock implementation
}

SimulationResult run_nru(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // NRU implementation
}

SimulationResult run_lfu(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // LFU implementation
}

SimulationResult run_mfu(const Reference *refs, int num_refs, int num_frames, bool verbose) {
    // MFU implementation
}