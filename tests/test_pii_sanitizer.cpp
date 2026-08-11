#include <iostream>
#include <cassert>
#include <string>
#include "guardrails/pii_sanitizer.h"

int main() {
    std::cout << "=== Running Unit Tests: Zero-Copy PII Sanitizer ===" << std::endl;

    guardrails::PIISanitizer sanitizer;

    // Test Case 1: Social Security Number (SSN) Redaction
    bool pii_found = false;
    std::string ssn_input = "My SSN is 123-45-6789, please keep it confidential.";
    std::string ssn_output = sanitizer.sanitize(ssn_input, pii_found);
    assert(pii_found == true);
    assert(ssn_output.find("[REDACTED_SSN]") != std::string::npos);
    assert(ssn_output.find("123-45-6789") == std::string::npos);
    std::cout << "  [PASS] SSN Redaction Output: " << ssn_output << std::endl;

    // Test Case 2: Email Redaction
    pii_found = false;
    std::string email_input = "Send the report to contact.user_99@domain.org as soon as possible.";
    std::string email_output = sanitizer.sanitize(email_input, pii_found);
    assert(pii_found == true);
    assert(email_output.find("[REDACTED_EMAIL]") != std::string::npos);
    assert(email_output.find("contact.user_99@domain.org") == std::string::npos);
    std::cout << "  [PASS] Email Redaction Output: " << email_output << std::endl;

    // Test Case 3: OpenAI / Cloud API Key Redaction
    pii_found = false;
    std::string key_input = "Use secret key sk-live-abc123xyz9876543210 for authentication.";
    std::string key_output = sanitizer.sanitize(key_input, pii_found);
    assert(pii_found == true);
    assert(key_output.find("[REDACTED_API_KEY]") != std::string::npos);
    assert(key_output.find("sk-live-abc123xyz9876543210") == std::string::npos);
    std::cout << "  [PASS] API Key Redaction Output: " << key_output << std::endl;

    // Test Case 4: Credit Card Number Redaction
    pii_found = false;
    std::string card_input = "Charge the total to card 4532-7112-9018-3411.";
    std::string card_output = sanitizer.sanitize(card_input, pii_found);
    assert(pii_found == true);
    assert(card_output.find("[REDACTED_CREDIT_CARD]") != std::string::npos);
    assert(card_output.find("4532-7112-9018-3411") == std::string::npos);
    std::cout << "  [PASS] Credit Card Redaction Output: " << card_output << std::endl;

    // Test Case 5: Clean Input without PII
    pii_found = false;
    std::string clean_input = "Tell me a joke about computer science.";
    std::string clean_output = sanitizer.sanitize(clean_input, pii_found);
    assert(pii_found == false);
    assert(clean_output == clean_input);
    std::cout << "  [PASS] Clean input passed unchanged." << std::endl;

    std::cout << "\n[+] PIISanitizer Unit Tests Passed Successfully!" << std::endl;
    return 0;
}