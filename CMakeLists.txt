cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(guardrails_cpp LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find LibTorch
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Include directories
include_directories(include ${TORCH_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/guardrail_engine.cpp
    src/prompt_injection.cpp
    src/pii_sanitizer.cpp
    src/safety_classifier.cpp
    src/kernels/token_scan_kernel.cu
)

# Build static library
add_library(guardrails_lib STATIC ${SOURCES})
target_link_libraries(guardrails_lib PUBLIC ${TORCH_LIBRARIES})

# Set CUDA targets
set_target_properties(guardrails_lib PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75;80;86;89;90"
)

# Build benchmark executable
add_executable(benchmark examples/benchmark.cpp)
target_link_libraries(benchmark PRIVATE guardrails_lib ${TORCH_LIBRARIES})