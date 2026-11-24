#include "algos.h"
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
    SimulationResult results;
    results.num_frames = num_frames;
		results.disk_writes = 0;
		results.total_refs = 0;
		results.evictions = 0;
		results.page_faults = 0;
    // queue for page ids
    Queue q;
    initializeQueue(&q);

    while(i < num_refs){
      results.total_refs++;
			if(refs[i].op == "W") results.disk_writes++;

      int frame_page = find_page(frames, num_frames, refs[i].page_id);
      // if the page isnt in any on the frames, there is a page fault
      if(frame_page == -1){
        results.page_faults++;

        int free_frame = find_free_frame(frames, num_frames);
        // if there is no free frame, a page is evicted following the algorithm rule
        if(free_frame == -1){
          dequeue(&q);
          enqueue(&q, refs[i].page_id);
          // put referenced page in new free frame
          free_frame = find_free_frame(frames, num_frames);

					// last used counts on both misses and hits
          frames[free_frame].last_used = i;
					// loaded at counts only on misses
					frames[free_frame].loaded_at = i;
					// freq count resets on a miss because a page was evicted from this frame
					frames[free_frame].freq_count = 1;

          results.evictions++;
        }

        frames[free_frame].page_id = refs[i].page_id;
      } 
			else {
        frames[frame_page].last_used = i;
				frames[frame_page].freq_count++;
      }

			i++;
    }

		results.final_frames = frames;

		return results;
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