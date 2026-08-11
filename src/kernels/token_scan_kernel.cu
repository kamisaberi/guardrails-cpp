#include "guardrails/kernels/token_scan_kernel.cuh"
#include <cuda_runtime.h>

namespace guardrails {
namespace kernels {

__global__ void scan_token_stream_kernel(
    const int32_t* __restrict__ tokens,
    int num_tokens,
    const int32_t* __restrict__ banned_tokens,
    int num_banned,
    int32_t* __restrict__ violation_flag) 
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < num_tokens) {
        int32_t token = tokens[tid];

        // Check token against array of banned jailbreak/toxic token IDs
        for (int b = 0; b < num_banned; ++b) {
            if (token == banned_tokens[b]) {
                // Set global atomic flag indicating safety policy violation
                atomicExch(violation_flag, 1);
                break;
            }
        }
    }
}

void launch_token_scan_kernel(
    const int32_t* tokens,
    int num_tokens,
    const int32_t* banned_tokens,
    int num_banned,
    int32_t* violation_flag,
    cudaStream_t stream) 
{
    int threads_per_block = 256;
    int blocks_per_grid = (num_tokens + threads_per_block - 1) / threads_per_block;

    scan_token_stream_kernel<<<blocks_per_grid, threads_per_block, 0, stream>>>(
        tokens, num_tokens, banned_tokens, num_banned, violation_flag
    );
}

} // namespace kernels
} // namespace guardrails