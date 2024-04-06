from setuptools import setup, Extension
from Cython.Build import cythonize

sample_extension = Extension(
    name="sample_wrapper",
    sources=["bridge/sample_bridge.pyx", "common/sample_bridge.cpp"],
    include_dirs=["include/astra-network-analytical/"],
    language="c++",
    extra_compile_args=["-std=c++11"],  # Or other C++ version as required
)

setup(
    name="astrasim_anoc_cython_wrapper",
    version="0.1",
    ext_modules=cythonize([sample_extension]),
)

