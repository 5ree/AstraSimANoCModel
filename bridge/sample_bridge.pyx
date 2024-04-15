# distutils: language = c++
# cython: language_level=3

cdef extern from "common/sample_bridge.h":
    void noc_setup()
    void sample_bridge_sanity()
    void chunk_arrived_callback(void* const chunk_ptr)
    void add_to_EQ(int SrcID, int DstId, int size)
    void simulate_events()

def py_noc_setup():
    noc_setup()

def py_common_bridge_sanity():
    sample_bridge_sanity()

def py_add_to_EQ (SrcID, DstId, size):
    print("Src: ", SrcID, " Dst: ", DstId, " Size: ", size)
    add_to_EQ(SrcID,DstId, size)

def py_simulate_events ():
    simulate_events()