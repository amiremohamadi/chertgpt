#ifndef OPTIMIZER_HH
#define OPTIMIZER_HH

#include <vector>

// https://pytorch.org/docs/stable/generated/torch.optim.AdamW.html
void adamw_optimizer(std::vector<std::vector<float>> &params, std::vector<std::vector<float>> &grads, 
                     std::vector<std::vector<float>> &m, std::vector<std::vector<float>> &v,
                     float lr, float beta1, float beta2, float epsilon, float weight_decay, int t);

#endif // OPTIMIZER_HH
