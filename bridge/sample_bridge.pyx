# distutils: language = c++
# cython: language_level=3

cdef extern from "common/sample_bridge.h":
    void sample_bridge_sanity()

def py_common_bridge_sanity():
    sample_bridge_sanity()
