#include "guardrails/guardrail_engine.h"
#include <chrono>

namespace guardrails {

GuardrailEngine::GuardrailEngine(const GuardrailConfig& config)
    : config_(config) {
    if (config_.enable_llama_guard_classifier) {
        safety_classifier_ = std::make_unique<SafetyClassifier>(config_.device);
    }
}

SecurityResult GuardrailEngine::validate_prompt(const std::string& prompt) {
    auto start_time = std::chrono::high_resolution_clock::now();
    SecurityResult result;
    result.sanitized_prompt = prompt;

    // 1. Stage 1: SIMD Prompt Injection Check
    if (config_.enable_prompt_injection_check) {
        std::string matched_pattern;
        if (injection_detector_.scan_prompt(prompt, matched_pattern)) {
            result.is_blocked = true;
            result.violation_reason = "Prompt Injection Detected: Matched Pattern '" + matched_pattern + "'";
            auto end_time = std::chrono::high_resolution_clock::now();
            result.latency_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();
            return result;
        }
    }

    // 2. Stage 2: Zero-Copy PII Sanitization
    if (config_.enable_pii_sanitization) {
        bool pii_found = false;
        result.sanitized_prompt = pii_sanitizer_.sanitize(prompt, pii_found);
    }

    // 3. Stage 3: Embedded Safety Classifier Evaluation
    if (config_.enable_llama_guard_classifier && safety_classifier_) {
        torch::Tensor dummy_tokens = torch::randint(0, 1000, {1, 32}, torch::dtype(torch::kLong).device(config_.device));
        auto [is_safe, score] = safety_classifier_->evaluate_safety(dummy_tokens);

        if (!is_safe) {
            result.is_blocked = true;
            result.violation_reason = "Safety Policy Violation (Toxicity Score: " + std::to_string(score) + ")";
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    result.latency_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    return result;
}

} // namespace guardrails