#include "common/sample_bridge.h" 
#include "common/EventQueue.h"
#include "common/NetworkParser.h"
#include "congestion_aware/Chunk.h"
#include "congestion_aware/Helper.h"
#include <iostream>

using namespace NetworkAnalytical;
using namespace NetworkAnalyticalCongestionAware;

std::shared_ptr<EventQueue> event_queue ;
std::shared_ptr<Topology> topology;
EventTime communication_start = 0;

void chunk_arrived_callback(void* const chunk_ptr) {
    auto* const chnkPtr = static_cast<Chunk*>(chunk_ptr);
    auto latency = chnkPtr->get_chunk_latency();
    latency = latency - communication_start;
    std::cout << "Src: " << chnkPtr->SrcID << " Dst: " << chnkPtr->DstId << " Latency: " << latency << " ns" << std::endl;
}

void noc_setup()
{
    std::cout << "SNDBG : Starting with noc_setup\n";
    // Instantiate shared resources
    event_queue = std::make_shared<EventQueue>();
    Topology::set_event_queue(event_queue);
    // Parse network config and create topology
    //"/home/hice1/snawandar3/krittika_hml_proj/dependencies/AstraSimANoCModel/input/Ring.yml"
    const auto network_parser = NetworkParser("./dependencies/AstraSimANoCModel/input/Ring.yml"); //FIXME this should come from input
    topology = construct_topology(network_parser);
    std::cout << "SNDBG : Done with noc_setup\n";
}

void add_to_EQ (int SrcID, int DstId, int size)
{
    // message settings
    const auto chunk_size = size;  // 1 MB
    const auto npus_count = topology->get_npus_count();

    // crate a chunk
    auto route = topology->route(SrcID, DstId);
    std::cout << "Scheduling chunk for Src: " << SrcID << " Dst " << DstId << std::endl;
    auto* event_queue_ptr = static_cast<void*>(event_queue.get());
    auto chunk = std::make_unique<Chunk>(chunk_size, route, chunk_arrived_callback, event_queue_ptr,SrcID,DstId);
    // send a chunk
    topology->send(std::move(chunk));

    std::cout << "SNDBG : Done with add_to_EQ\n";
}

void simulate_events ()
{
    communication_start = event_queue->get_current_time();
    std::cout << "Communication Start time is : " << communication_start << " ns"<< std::endl;
    // Run simulation
    while (!event_queue->finished()) {
        event_queue->proceed();
    }
        std::cout << "SNDBG : Done with  simulate_event \n";
}

void sample_bridge_sanity()
{
    std::cout << "SREEMANTH:  CALLING THIS FROM ANOC MODEL!\n";
}