#include "common/sample_bridge.h" 
#include "common/EventQueue.h"
#include "common/NetworkParser.h"
#include "congestion_aware/Chunk.h"
#include "congestion_aware/Helper.h"
#include "common/Logger.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace NetworkAnalytical;
using namespace NetworkAnalyticalCongestionAware;

std::shared_ptr<EventQueue> event_queue ;
std::shared_ptr<Topology> topology;
EventTime communication_start = 0;

void chunk_arrived_callback(void* const chunk_ptr)
{
    auto* const chnkPtr = static_cast<Chunk*>(chunk_ptr);
    auto latency = chnkPtr->get_chunk_latency();
    latency = latency - communication_start;

    std::stringstream ss;
    ss << "Src: " << chnkPtr->SrcID << " Dst: " << chnkPtr->DstId << " Latency: " << latency << " ns";
    INFO(ss.str());
}

void noc_setup(const std::string filePath)
{
    std::stringstream ss;
    ss << "Starting with noc_setup";
    DEBUG(ss.str());

    // Instantiate shared resources
    event_queue = std::make_shared<EventQueue>();
    Topology::set_event_queue(event_queue);

    // Parse network config and create topology
    const auto network_parser = NetworkParser(filePath);
    topology = construct_topology(network_parser);
    
    ss.str(""); ss.clear();
    ss << "Done with noc_setup";
    DEBUG(ss.str());
}

void add_to_EQ (int SrcID, int DstId, int size)
{
    std::stringstream ss;

    // message settings
    // TODO:
    //  - We need to add logic to split size into chunks based on network config
    const auto chunk_size = size;  // 1 MB
    const auto npus_count = topology->get_npus_count();

    // crate a chunk
    ss << "Scheduling chunk for Src: " << SrcID << " Dst " << DstId;
    INFO(ss.str());

    auto route = topology->route(SrcID, DstId);
    auto* event_queue_ptr = static_cast<void*>(event_queue.get());
    auto chunk = std::make_unique<Chunk>(chunk_size, route, chunk_arrived_callback, event_queue_ptr,SrcID,DstId);

    // send a chunk
    topology->send(std::move(chunk));

    ss.str(""); ss.clear();
    ss << "Done with add_to_EQ";
    DEBUG(ss.str());
}

void simulate_events ()
{
    std::stringstream ss;
    
    communication_start = event_queue->get_current_time();
    ss << "Communication Start time is : " << communication_start << " ns";
    INFO(ss.str());

    // Run simulation
    while (!event_queue->finished()) {
        event_queue->proceed();
    }
        
    ss.str(""); ss.clear();
    ss << "Done with simulate_event";
    DEBUG(ss.str());
}

void sample_bridge_sanity()
{
    std::stringstream ss;
    ss << "Sanity print from the ANOC Cython binding";
    INFO(ss.str());
}