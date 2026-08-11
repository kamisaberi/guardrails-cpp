#ifndef GUARDRAILS_SAFETY_CLASSIFIER_H
#define GUARDRAILS_SAFETY_CLASSIFIER_H

#include <torch/torch.h>
#include <memory>
#include <utility>

namespace guardrails {

class SafetyClassifier {
public:
    explicit SafetyClassifier(torch::Device device);

    // Runs forward evaluation using embedded LibTorch/TensorRT model engine
    std::pair<bool, float> evaluate_safety(const torch::Tensor& input_tokens);

private:
    torch::Device device_;
    std::shared_ptr<torch::nn::Sequential> dummy_classifier_;
};

} // namespace guardrails

#endif // GUARDRAILS_SAFETY_CLASSIFIER_H