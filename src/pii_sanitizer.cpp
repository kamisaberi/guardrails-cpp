#include "guardrails/pii_sanitizer.h"

namespace guardrails {

PIISanitizer::PIISanitizer() {
    // Optimized Regex Patterns for PII Detection
    ssn_regex_          = std::regex(R"(\b\d{3}-\d{2}-\d{4}\b)", std::regex::optimize);
    email_regex_        = std::regex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)", std::regex::optimize);
    api_key_regex_      = std::regex(R"(\bsk-[a-zA-Z0-9_-]{12,}\b)", std::regex::optimize);
    credit_card_regex_  = std::regex(R"(\b(?:\d{4}[- ]?){3}\d{4}\b)", std::regex::optimize);
}

std::string PIISanitizer::sanitize(const std::string& input, bool& pii_found) const {
    std::string result = input;
    pii_found = false;

    // Redact SSN
    if (std::regex_search(result, ssn_regex_)) {
        result = std::regex_replace(result, ssn_regex_, "[REDACTED_SSN]");
        pii_found = true;
    }

    // Redact Emails
    if (std::regex_search(result, email_regex_)) {
        result = std::regex_replace(result, email_regex_, "[REDACTED_EMAIL]");
        pii_found = true;
    }

    // Redact API Keys
    if (std::regex_search(result, api_key_regex_)) {
        result = std::regex_replace(result, api_key_regex_, "[REDACTED_API_KEY]");
        pii_found = true;
    }

    // Redact Credit Cards
    if (std::regex_search(result, credit_card_regex_)) {
        result = std::regex_replace(result, credit_card_regex_, "[REDACTED_CREDIT_CARD]");
        pii_found = true;
    }

    return result;
}

} // namespace guardrails