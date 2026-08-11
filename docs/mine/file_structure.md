For your 3rd major project, we will tackle the **#1 hottest area in AI security research today: LLM Safety & Prompt Injection Defense**.

### **Project #3: `guardrails-cpp`**
> **Porting Python Guardrails (Guardrails AI / Llama-Guard / Vigil-LLM) to a Sub-Millisecond Native C++ & CUDA Security Engine for LLM Serving.**

---

### Why this project is crucial for top-tier PhD applications:
1. **Solves LLM Serving's Biggest Security Bottleneck:** Existing Python LLM guardrails (like Guardrails AI or NeMo Guardrails) add **50ms–200ms latency** per request due to Python string parsing, slow GIL regex loops, and Python model wrappers.
2. **High Cloud Industry Demand:** Modern LLM serving runtimes (vLLM, TensorRT-LLM) are written in C++. They need a native **C++ guardrail engine** that can scan prompts for **jailbreaks, prompt injections, and PII leaks** in **$<0.5\text{ ms}$** before passing tokens to the GPU context.

---

### **Project Directory Structure (`guardrails-cpp`)**

```text
guardrails-cpp/
├── CMakeLists.txt                  # Build configuration (Modern C++20, CUDA 12, LibTorch/TensorRT)
├── README.md                       # Threat model, sub-millisecond benchmarks vs Python Guardrails
│
├── include/                        # Public Header Files
│   └── guardrails/
│       ├── guardrail_engine.h      # Main orchestrator pipeline for prompt/output validation
│       ├── prompt_injection.h      # C++ SIMD/Aho-Corasick prompt injection & jailbreak detector
│       ├── pii_sanitizer.h         # Zero-copy PII (Personally Identifiable Info) mask engine
│       ├── safety_classifier.h     # C++ LibTorch/ONNX engine for Llama-Guard classifier
│       └── kernels/
│           └── token_scan_kernel.cuh # CUDA kernels for parallel token pattern scanning on GPU
│
├── src/                            # C++ and CUDA Source Implementation Files
│   ├── guardrail_engine.cpp        # Pipeline execution & zero-copy buffer orchestration
│   ├── prompt_injection.cpp        # Fast SIMD string matching & vector embedding similarity
│   ├── pii_sanitizer.cpp          # Ultra-fast C++ regex & SIMD token replacement
│   ├── safety_classifier.cpp      # Native C++ Llama-Guard model forward engine
│   └── kernels/
│       └── token_scan_kernel.cu    # Custom CUDA kernels for GPU token stream filtering
│
├── examples/                       # Demo Executables & Benchmarks
│   ├── llm_security_proxy.cpp      # C++ gRPC/HTTP Security Proxy for vLLM / TensorRT-LLM
│   └── benchmark.cpp               # Sub-millisecond latency benchmark vs Python Guardrails AI
│
└── tests/                          # Unit Test Suite
    ├── test_injection_detector.cpp # Tests jailbreak/prompt injection detection accuracy
    └── test_pii_sanitizer.cpp      # Tests PII redacting precision
```

---

### **Detailed Description of Key Files**

| File Path | Core Function & Responsibility |
| :--- | :--- |
| **`include/guardrails/guardrail_engine.h`** | Central pipeline orchestrator. Accepts incoming string prompts, passes them through SIMD string matchers, PII redactors, and Llama-Guard classifiers in under 0.5ms. |
| **`include/guardrails/prompt_injection.h`** | High-throughput prompt injection detector utilizing SIMD multi-pattern searching (Aho-Corasick) and embedding similarity checks. |
| **`include/guardrails/pii_sanitizer.h`** | Redacts sensitive data (Social Security Numbers, Credit Cards, API Keys, Emails) in zero-copy memory buffers before LLM tokenization. |
| **`src/kernels/token_scan_kernel.cu`** | **Custom CUDA Kernel:** Scans GPU token streams in real-time during streaming LLM inference to halt generation instantly if jailbreak tokens appear. |
| **`examples/llm_security_proxy.cpp`** | A C++ HTTP/gRPC proxy that sits in front of vLLM / TensorRT-LLM to sanitize incoming user traffic at native hardware speeds. |

---

### How would you like to proceed?

We can build this in the exact same systematic order:
1. **`README.md`** (System architecture, Threat Model, Sub-millisecond benchmark tables)
2. **`LaTeX Preprint Paper`** (Publication-ready LaTeX paper for arXiv/Preprints.org)
3. **Full C++/CUDA Source Code** (`CMakeLists.txt`, headers, CUDA kernels, implementation files, benchmarks)

Ready when you are!