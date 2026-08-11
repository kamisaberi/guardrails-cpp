#include "guardrails/prompt_injection.h"
#include <algorithm>
#include <cctype>

namespace guardrails {

PromptInjectionDetector::PromptInjectionDetector() {
    // Default known jailbreak and prompt injection patterns
    injection_patterns_ = {
        "ignore all previous instructions",
        "ignore system prompt",
        "system prompt override",
        "reveal system prompt",
        "dan mode",
        "do anything now",
        "jailbreak",
        "act as an unfiltered ai",
        "bypass safety restrictions"
    };
}

std::string PromptInjectionDetector::to_lower(const std::string& str) const {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lower_str;
}

void PromptInjectionDetector::add_pattern(const std::string& pattern) {
    injection_patterns_.push_back(to_lower(pattern));
}

bool PromptInjectionDetector::scan_prompt(const std::string& prompt, std::string& matched_pattern) const {
    std::string lower_prompt = to_lower(prompt);

    for (const auto& pattern : injection_patterns_) {
        if (lower_prompt.find(pattern) != std::string::npos) {
            matched_pattern = pattern;
            return true; // Injection detected
        }
    }
    return false; // Safe
}

} // namespace guardrails