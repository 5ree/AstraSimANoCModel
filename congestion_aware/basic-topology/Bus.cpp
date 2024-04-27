/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#include "congestion_aware/Bus.h"
#include "congestion_aware/Link.h"
#include <cassert>

using namespace NetworkAnalyticalCongestionAware;

Bus::Bus(const int npus_count, const Bandwidth bandwidth, const Latency latency) noexcept
    : BasicTopology(npus_count, npus_count + 1, bandwidth, latency) {
    assert(npus_count > 0);
    assert(bandwidth > 0);
    assert(latency >= 0);

    // Create the common bus link
    auto bus_link = std::make_shared<Link>(bandwidth, latency);

    // Use this bus_link to connect all npus to each other
    for (auto i = 0; i < npus_count; i++) {
    {
        for (auto j = 0; j < npus_count; j++)
        {
            if (i != j)
            {
                devices[i]->map_link(j, bus_link);
            }
        }
    }
    }
}

Route Bus::route(DeviceId src, DeviceId dest) const noexcept {
    // assert npus are in valid range
    assert(0 <= src && src < npus_count);
    assert(0 <= dest && dest < npus_count);

    // construct route, which is the same bus for anything
    auto route = Route();
    route.push_back(devices[src]);
    route.push_back(devices[dest]);

    return route;
}
