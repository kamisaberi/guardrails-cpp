#ifndef GUARDRAILS_TOKEN_SCAN_KERNEL_CUH
#define GUARDRAILS_TOKEN_SCAN_KERNEL_CUH

#include <cuda_runtime.h>
#include <cstdint>

namespace guardrails {
namespace kernels {

// CUDA Kernel launcher: Parallel real-time GPU token stream scanner for safety violations
void launch_token_scan_kernel(
    const int32_t* tokens,
    int num_tokens,
    const int32_t* banned_tokens,
    int num_banned,
    int32_t* violation_flag,
    cudaStream_t stream = 0
);

} // namespace kernels
} // namespace guardrails

#endif // GUARDRAILS_TOKEN_SCAN_KERNEL_CUH