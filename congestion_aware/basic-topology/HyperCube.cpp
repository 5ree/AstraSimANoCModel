/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#include "congestion_aware/HyperCube.h"
#include "common/Logger.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace NetworkAnalyticalCongestionAware;

HyperCube::HyperCube(const int npus_count, const Bandwidth bandwidth, const Latency latency) noexcept
    : BasicTopology(npus_count, npus_count, bandwidth, latency) {
    assert(npus_count > 0);
    assert(bandwidth > 0);
    assert(latency >= 0);

    // set topology type
    basic_topology_type = TopologyBuildingBlock::HyperCube;

    int dimensions = std::log2(npus_count);
    if (std::pow(2, dimensions) != npus_count) {
        std::cerr << "Error: npus_count must be a power of 2." << std::endl;
    }

    std::stringstream ss;
    ss << "HyperCube being constructed with dims = " << dimensions << ", npus_count = " << npus_count << ", bandwidth = " << bandwidth << ", latency = " << latency; 
    DEBUG(ss.str());

    // Set up connections for a hypercube topology
    for (int src = 0; src < npus_count; src++) {
        for (int i = 0; i < dimensions; i++) {
            int dest = src ^ (1 << i); // Flip the i-th bit of src to find its neighbor
            if (src < dest) { // This check ensures that each connection is set up only once

                ss.str(""); ss.clear();
                ss << "Connecting NPU " << src << " to NPU " << dest << " with bandwidth = " << bandwidth << " and latency = " << latency;
                DEBUG(ss.str());

                connect(src, dest, bandwidth, latency, true);
            }
        }
    }
}

Route HyperCube::route(const DeviceId src, const DeviceId dest) const noexcept {
    // assert npus are in valid range
    assert(0 <= src && src < npus_count);
    assert(0 <= dest && dest < npus_count);

    // construct route
    auto route = Route();
    route.push_back(devices[src]);

    // Calculate the difference using bitwise XOR
    DeviceId current = src;
    DeviceId path = src ^ dest;

    // Determine the number of dimensions (assuming npus_count is a power of 2)
    int dimensions = std::log2(npus_count);

    for (int i = 0; i < dimensions; i++) {
        // Check if the i-th bit is set in the path
        if (path & (1 << i)) {
            // Toggle the i-th bit in current to move to the next hop
            current ^= (1 << i);
            route.push_back(devices[current]);
        }
    }

    std::stringstream ss;
    ss << "Route from NPU " << src << " to NPU " << dest << " is: \n";
    for (const auto& device : route) {
        ss << device->get_id() << " -> ";
    }
    DEBUG(ss.str());

    return route;
}
