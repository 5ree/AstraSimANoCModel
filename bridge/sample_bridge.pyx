# distutils: language = c++
# cython: language_level=3

from libcpp.string cimport string

cdef extern from "common/sample_bridge.h":
    void noc_setup(string filepath)
    void sample_bridge_sanity()
    void chunk_arrived_callback(void* const chunk_ptr)
    int add_to_EQ(int clk, int SrcID, int DstId, int size)
    void simulate_events()
    int get_latency(int t_id) 
    int get_static_latency(int src, int dest, int size);

def py_noc_setup(filepath):
    noc_setup(filepath)

def py_common_bridge_sanity():
    sample_bridge_sanity()

def py_add_to_EQ(clk, SrcID, DstId, size):
    t_id = add_to_EQ(clk, SrcID,DstId, size)
    return t_id

def py_simulate_events ():
    simulate_events()

def py_get_latency(t_id):
    lat = get_latency(t_id)
    return lat

def py_get_static_latency(src, dest, size):
    stat_lat = get_static_latency(src, dest, size)
    return stat_lat