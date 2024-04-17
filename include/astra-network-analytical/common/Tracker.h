#pragma once

#include <map>
#include <cstddef>

namespace NetworkAnalytical
{
    class Tracker {
    private:
        static std::map<size_t, int> tracker;
        static size_t num_tracked;

    public:
        static size_t create();
        static void update(size_t t_id, int lat);
        static int lookup(size_t t_id);
        static void print(); 
    };
} 
