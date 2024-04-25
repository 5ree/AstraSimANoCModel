#pragma once
#include "congestion_aware/Chunk.h"

void noc_setup(const std::string filePath);
void sample_bridge_sanity();
void chunk_arrived_callback(void* const chunk_ptr);
int add_to_EQ(int clk, int SrcID, int DstId, int size);
void simulate_events();
int get_latency(size_t t_id);
void schedule_chunk(void* arg);
int get_static_latency(int src, int dest, int size);