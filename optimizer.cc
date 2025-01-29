#include <cmath>
#include "optimizer.hh"

// https://pytorch.org/docs/stable/generated/torch.optim.AdamW.html
// FIXME
void adamw_optimizer(std::vector<std::vector<float>>& params, std::vector<std::vector<float>>& grads, 
                     std::vector<std::vector<float>>& m, std::vector<std::vector<float>>& v,
                     float lr, float beta1, float beta2, float epsilon, float weight_decay, int t) {
    for (int i = 0; i < params.size(); ++i) {
        for (int j = 0; j < params[i].size(); ++j) {
            m[i][j] = beta1 * m[i][j] + (1 - beta1) * grads[i][j];
            v[i][j] = beta2 * v[i][j] + (1 - beta2) * grads[i][j] * grads[i][j];

            float m_hat = m[i][j] / (1 - std::pow(beta1, t));
            float v_hat = v[i][j] / (1 - std::pow(beta2, t));

            params[i][j] -= lr * (m_hat / (std::sqrt(v_hat) + epsilon) + weight_decay * params[i][j]);
        }
    }
}
