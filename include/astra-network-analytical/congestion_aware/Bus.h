/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#pragma once

#include "common/Type.h"
#include "congestion_aware/BasicTopology.h"
#include <cassert>

using namespace NetworkAnalytical;

namespace NetworkAnalyticalCongestionAware {

    /**
 * Implements a Bus topology.
 *
 * Switch(4) example:
 * ----------
 * |  |  |  |
 * 0  1  2  3
 *
 * Everything shares the same bus link
 */
    class Bus final : public BasicTopology {
    public:
        /**
   * Constructor.
   *
   * @param npus_count number of npus connected to the switch
   * @param bandwidth bandwidth of link
   * @param latency latency of link
   */
        Bus(int npus_count, Bandwidth bandwidth, Latency latency) noexcept;

        /**
   * Implementation of route function in Topology.
   */
        [[nodiscard]] Route route(DeviceId src, DeviceId dest) const noexcept override;
    };

}  // namespace NetworkAnalyticalCongestionAware
