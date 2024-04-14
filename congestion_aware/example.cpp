/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#include "common/EventQueue.h"
#include "common/NetworkParser.h"
#include "congestion_aware/Chunk.h"
#include "congestion_aware/Helper.h"
#include <iostream>

using namespace NetworkAnalytical;
using namespace NetworkAnalyticalCongestionAware;

EventTime communication_start = 0;
void chunk_arrived_callback(void* const chunk_ptr) {
    auto* const chnkPtr = static_cast<Chunk*>(chunk_ptr);
    auto latency = chnkPtr->get_chunk_latency();
    latency = latency - communication_start;
    std::cout << "Src: " << chnkPtr->SrcID << " Dst: " << chnkPtr->DstId << " Latency: " << latency << " ns" << std::endl;
}

int main() {
    // Instantiate shared resources
    const auto event_queue = std::make_shared<EventQueue>();
    Topology::set_event_queue(event_queue);

    // Parse network config and create topology
    const auto network_parser = NetworkParser("../input/Ring.yml");
    const auto topology = construct_topology(network_parser);
    const auto npus_count = topology->get_npus_count();
    const auto devices_count = topology->get_devices_count();

    // message settings
    const auto chunk_size = 1'048'576;  // 1 MB

    // Run All-Gather
    for (int i = 0; i < npus_count; i++) {
        for (int j = 0; j < npus_count; j++) {
            if (i == j) {
                continue;
            }
            // crate a chunk
            auto route = topology->route(i, j);
            std::cout << "Scheduling chunk for Src: " << i << " Dst " << j << std::endl;
            auto* event_queue_ptr = static_cast<void*>(event_queue.get());
            auto chunk = std::make_unique<Chunk>(chunk_size, route, chunk_arrived_callback, event_queue_ptr,i,j);

            // send a chunk
            topology->send(std::move(chunk));
        }
    }
    communication_start = event_queue->get_current_time();
    std::cout << "Communication Start time is : " << communication_start << " ns"<< std::endl;
    // Run simulation
    while (!event_queue->finished()) {
        event_queue->proceed();
    }

    // Print simulation result
    const auto finish_time = event_queue->get_current_time();
    std::cout << "Total NPUs Count: " << npus_count << std::endl;
    std::cout << "Total devices Count: " << devices_count << std::endl;
    std::cout << "Simulation finished at time: " << finish_time << " ns" << std::endl;

    return 0;
}
