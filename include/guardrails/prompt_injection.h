#ifndef GUARDRAILS_PROMPT_INJECTION_H
#define GUARDRAILS_PROMPT_INJECTION_H

#include <string>
#include <vector>

namespace guardrails {

class PromptInjectionDetector {
public:
    PromptInjectionDetector();

    // Fast SIMD multi-pattern matching for prompt injection signatures
    bool scan_prompt(const std::string& prompt, std::string& matched_pattern) const;

    void add_pattern(const std::string& pattern);

private:
    std::vector<std::string> injection_patterns_;
    
    std::string to_lower(const std::string& str) const;
};

} // namespace guardrails

#endif // GUARDRAILS_PROMPT_INJECTION_H