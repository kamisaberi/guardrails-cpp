enable_testing()

# Injection Detector Unit Test
add_executable(test_injection_detector tests/test_injection_detector.cpp)
target_link_libraries(test_injection_detector PRIVATE guardrails_lib ${TORCH_LIBRARIES})
add_test(NAME TestPromptInjection COMMAND test_injection_detector)

# PII Sanitizer Unit Test
add_executable(test_pii_sanitizer tests/test_pii_sanitizer.cpp)
target_link_libraries(test_pii_sanitizer PRIVATE guardrails_lib ${TORCH_LIBRARIES})
add_test(NAME TestPIISanitizer COMMAND test_pii_sanitizer)