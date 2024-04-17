#pragma once
#include "congestion_aware/Chunk.h"

void noc_setup(const std::string filePath);
void sample_bridge_sanity();
void chunk_arrived_callback(void* const chunk_ptr);
int add_to_EQ(int SrcID, int DstId, int size);
void simulate_events();
int get_latency(size_t t_id);