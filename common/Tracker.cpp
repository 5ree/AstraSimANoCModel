#include "common/Tracker.h"
#include "common/Logger.h"

using namespace NetworkAnalytical;

std::map<size_t, int> Tracker::tracker;
size_t Tracker::num_tracked = 0;

size_t Tracker::create()
{
    size_t t_id = num_tracked;    
    tracker[t_id] = -1;

    std::stringstream ss;
    ss << "Created tracking id " << t_id << " in the tracker";
    DEBUG(ss.str());
    print();

    num_tracked++;
    return t_id;
}

void Tracker::update(size_t t_id, int lat)
{
    auto it = tracker.find(t_id);
    if (it != tracker.end())
    {
        it->second = lat;
    }
    else
    {
        std::stringstream ss;
        ss << "Tracker id " << t_id << " not found in the tracker";
        WARNING(ss.str());
    }

    print();
}

int Tracker::lookup(size_t t_id)
{
    auto it = tracker.find(t_id);
    if (it != tracker.end())
    {
        return it->second;
    }
    else
    {
        std::stringstream ss;
        ss << "Tracker id " << t_id << " not found in the tracker";
        WARNING(ss.str());
        return -1;
    }

    print();
}

void Tracker::print() {
    std::stringstream ss;
    ss << "Contents of the tracker:";

    for (const auto& pair : tracker) {
        ss << "\n\tKey: " << pair.first << ", Value: " << pair.second;
    }

    DEBUG(ss.str());
}