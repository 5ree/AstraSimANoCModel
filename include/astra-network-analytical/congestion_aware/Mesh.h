/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#pragma once

#include "common/Type.h"
#include "congestion_aware/BasicTopology.h"

using namespace NetworkAnalytical;

namespace NetworkAnalyticalCongestionAware {

    /**
 * Implements a Mesh topology.
 *
 * Mesh(8) example:
 * 0 -  1 - 2 -  3
   |    |   |    |
 * 4 -  5 - 6 -  7
   |    |   |    |
 * 8 -  9 - 10 - 11
   |    |   |    |
 *12 - 13 - 14 - 15
 *
 
 */
    class Mesh final : public BasicTopology {
    public:
        /**
   * Constructor.
   *
   * @param npus_count number of npus in a Mesh
   * @param bandwidth bandwidth of link
   * @param latency latency of link
   * @param bidirectional true if Mesh is bidirectional, false otherwise
   */
        Mesh(int Rows, int Cols, Bandwidth bandwidth, Latency latency) noexcept;

        /**
   * Implementation of route function in Topology.
   */
        [[nodiscard]] Route route(DeviceId src, DeviceId dest) const noexcept override;
    };

}  // namespace NetworkAnalyticalCongestionAware
