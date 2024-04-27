/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#include "congestion_aware/Mesh.h"
#include <cassert>
#include <iostream>

using namespace NetworkAnalyticalCongestionAware;

int glob_rows;
int glob_cols;

Mesh::Mesh(const int rows, const int cols, const Bandwidth bandwidth, const Latency latency) noexcept
    : BasicTopology(rows*cols, rows*cols, bandwidth, latency) {
    assert(rows>0);
    assert(cols>0);
    assert(bandwidth > 0);
    assert(latency >= 0);

    int src ;
    int dest;
    // connect npus in a Mesh
    // connect only right and bottom neighbour to avoid duplicate connections.
    for (auto i = 0; i < rows ; i++) {
        for (auto j=0 ; j < cols ; j++){
            src = i*(cols) + j;
            //connect to right neighbor if exists
            if( j+1 < cols) {
                dest = i*(cols) + j+1;
                connect(src, dest, bandwidth, latency, true);
            }
            if( i+1 < rows) {
                dest = (i+1)*(cols) + j;
                connect(src, dest, bandwidth, latency, true);
            }
        }
    }
    glob_rows = rows;
    glob_cols = cols;
}

Route Mesh::route(DeviceId src, DeviceId dest) const noexcept {
    // assert npus are in valid range
    assert(0 <= src && src < npus_count);
    assert(0 <= dest && dest < npus_count);

    // construct empty route
    auto route = Route();

    int srci = src / glob_cols;
    int srcj = src % glob_cols;
    int desti = dest / glob_cols;
    int destj = dest % glob_cols;
    DeviceId curr;
    //default direction is first right then down.

    int curRow = srci;
    int curCol = srcj;
    // Determine the row direction (up or down)
    int rowDirection = (desti >= srci) ? 1 : -1;

    // Move vertically (up or down) until reaching the destination row
    while (curRow != desti) {
        curr = (curRow*glob_cols) + curCol;
        route.push_back(devices[curr]);
        curRow += rowDirection;
    }

    int colDirection = (destj >= srcj) ? 1 : -1;
    // Move horizontally (left or right) until reaching the destination column
    while (curCol != destj) {
        curr = (curRow*glob_cols) + curCol;
        route.push_back(devices[curr]);
        curCol += colDirection;
    }
    // arrives at dest
    route.push_back(devices[dest]);

    // return the constructed route
    return route;
}
