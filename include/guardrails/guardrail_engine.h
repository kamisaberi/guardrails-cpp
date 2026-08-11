#ifndef GUARDRAILS_GUARDRAIL_ENGINE_H
#define GUARDRAILS_GUARDRAIL_ENGINE_H

#include <string>
#include <memory>
#include <torch/torch.h>
#include "guardrails/prompt_injection.h"
#include "guardrails/pii_sanitizer.h"
#include "guardrails/safety_classifier.h"

namespace guardrails {

struct GuardrailConfig {
    bool enable_prompt_injection_check = true;
    bool enable_pii_sanitization = true;
    bool enable_llama_guard_classifier = true;
    torch::Device device = torch::kCPU;
};

struct SecurityResult {
    bool is_blocked = false;
    std::string violation_reason;
    std::string sanitized_prompt;
    double latency_ms = 0.0;
};

class GuardrailEngine {
public:
    explicit GuardrailEngine(const GuardrailConfig& config);

    // Core validation pipeline
    SecurityResult validate_prompt(const std::string& prompt);

private:
    GuardrailConfig config_;
    PromptInjectionDetector injection_detector_;
    PIISanitizer pii_sanitizer_;
    std::unique_ptr<SafetyClassifier> safety_classifier_;
};

} // namespace guardrails

#endif // GUARDRAILS_GUARDRAIL_ENGINE_H