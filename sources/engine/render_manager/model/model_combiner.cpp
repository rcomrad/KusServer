#include "model_combiner.hpp"

namespace kusengine::render
{

// void
// ModelCombiner::sortByMaterial(std::vector<std::unique_ptr<Model>>& models)
// const
// {
//     auto sort_lambda =
//         [](std::unique_ptr<Model>& left, std::unique_ptr<Model>& right)
//     {
//         auto& left_meshes  = left->takeMeshes();
//         auto& right_meshes = right->takeMeshes();

//     };
// }

void
ModelCombiner::combine(const std::vector<std::unique_ptr<Model>>& models)
{
    std::vector<const Mesh*> all_meshes;

    for (int i = 0; i < models.size(); ++i)
    {
        models[i]->pushTo(all_meshes);
    }
}

} // namespace kusengine::render
