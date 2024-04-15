import os
import glob
from setuptools import setup, Extension
from Cython.Build import cythonize

# Define the root directory for recursive search
root_dir = "."

# List to collect all matching .cpp files
cpp_sources = []

# Function to determine if a directory should be skipped
def should_skip_dir(dir_path):
    # Define directories to skip (add more as needed)
    skip_dirs = ["extern","test","bridge","build"]
    # Check if the directory name matches any of the skip directories
    return any(skip_dir in dir_path for skip_dir in skip_dirs)

# Recursively traverse the directory tree starting from root_dir
for root, dirs, files in os.walk(root_dir):
    # Check if current directory should be skipped
    if should_skip_dir(root):
        continue
    # Use glob.glob to find all .cpp files in the current directory
    cpp_files = glob.glob(os.path.join(root, "*.cpp"))
    # Extend cpp_sources list with the matched .cpp files
    cpp_sources.extend(cpp_files)


# Remove files from cpp_sources based on filename pattern
unwanted_files = ["example.cpp"]
cpp_sources = [file for file in cpp_sources if os.path.basename(file) not in unwanted_files]

# Print the cpp_sources list
print("List of matched .cpp files:")
for cpp_file in cpp_sources:
    print(cpp_file)

sample_extension = Extension(
    name="sample_wrapper",
    sources=["bridge/sample_bridge.pyx"] + cpp_sources,
    include_dirs=["include/astra-network-analytical/"],
    libraries=["yaml-cpp"],
    language="c++",
    extra_compile_args=["-std=c++14"],  # Or other C++ version as required
)

setup(
    name="astrasim_anoc_cython_wrapper",
    version="0.1",
    ext_modules=cythonize([sample_extension]),
)
