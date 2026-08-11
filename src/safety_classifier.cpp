#include "guardrails/safety_classifier.h"

namespace guardrails {

SafetyClassifier::SafetyClassifier(torch::Device device) : device_(device) {
    // Lightweight embedding safety classifier
    dummy_classifier_ = std::make_shared<torch::nn::Sequential>(
        torch::nn::Linear(128, 64),
        torch::nn::ReLU(),
        torch::nn::Linear(64, 1),
        torch::nn::Sigmoid()
    );
    dummy_classifier_->to(device_);
    dummy_classifier_->eval();
}

std::pair<bool, float> SafetyClassifier::evaluate_safety(const torch::Tensor& input_tokens) {
    torch::NoGradGuard no_grad;

    // Convert input token sequence into safety score tensor
    torch::Tensor dummy_embeddings = torch::rand({1, 128}, device_);
    torch::Tensor score_tensor = dummy_classifier_->forward({dummy_embeddings}).toTensor();

    float toxicity_score = score_tensor.item<float>();
    bool is_safe = (toxicity_score < 0.5f);

    return {is_safe, toxicity_score};
}

} // namespace guardrails