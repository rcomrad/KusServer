// #include "drawable_system.hpp"

// #include <iostream>

// #include "engine/graphics/renderer/swap_chain_frame.hpp"
// namespace kusengine
// {
// // void
// // DrawableSystem::add(Drawable* const no_temparary_drawable)
// // {
// //     if (no_temparary_drawable)
// //     {
// //         m_drawables.emplace_back(no_temparary_drawable);
// //     }
// // }

// DrawableSystem::DrawableSystem() : is_empty(true)
// {
// }

// void
// DrawableSystem::updateMBDD(SwapChainFrame& frame) const
// {
//     if (is_empty) return;

//     frame.updateMBDD(mbdd_data_vector);
// }

// void
// DrawableSystem::generate()
// {
//     if (is_empty) return;
//     int count = m_drawables.size();

//     mbdd_data_vector.resize(count);

//     std::vector<std::pair<uint32_t, uint32_t>> inds(count);

//     for (int i = 0; i < count; ++i)
//     {
//         auto& drawable = m_drawables[i];
//         auto index     = drawable->pushModel(m_model_storage);

//         inds[i].first  = i;
//         inds[i].second = index;
//     }

//     std::sort(inds.begin(), inds.end(), [](const auto& left, const auto&
//     right)
//               { return left.second < right.second; });

//     for (int i = 0; i < count; ++i)
//     {
//         int cor_index = inds[i].first;

//         m_drawables[cor_index]->linkData(&(mbdd_data_vector[i]));
//         m_drawables[i]->updModelMatrix();
//     }

//     m_model_storage.fillBuffers();
// }

// void
// DrawableSystem::draw(const vk::CommandBuffer& command_buffer,
//                      const vk::PipelineLayout& pipelayout,
//                      SwapChainFrame& frame) const
// {
//     if (is_empty) return;
//     m_model_storage.bind(command_buffer);

//     m_model_storage.draw(command_buffer, pipelayout);
// }
// }; // namespace kusengine
