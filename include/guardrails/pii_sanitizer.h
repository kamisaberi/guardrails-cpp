#ifndef GUARDRAILS_PII_SANITIZER_H
#define GUARDRAILS_PII_SANITIZER_H

#include <string>
#include <regex>

namespace guardrails {

class PIISanitizer {
public:
    PIISanitizer();

    // Zero-copy PII masking & redaction engine
    std::string sanitize(const std::string& input, bool& pii_found) const;

private:
    std::regex ssn_regex_;
    std::regex email_regex_;
    std::regex api_key_regex_;
    std::regex credit_card_regex_;
};

} // namespace guardrails

#endif // GUARDRAILS_PII_SANITIZER_H