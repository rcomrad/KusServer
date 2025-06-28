#ifndef BASE_MABDDI_HPP
#define BASE_MABDDI_HPP
#include "engine/render_manager/dynamics_data/mbddi_buffer/mbddi_buffer.hpp"

namespace kusengine::render
{

template <typename MBDD_T>
class BaseMBDDI : public MBDDIBuffer<MBDD_T>
{
public:
    void linkData(MBDD_T* new_data);

private:
};

template <typename MBDD_T>
void
BaseMBDDI<MBDD_T>::linkData(MBDD_T* new_data)
{
    if (new_data != MBDDIBuffer<MBDD_T>::m_data)
    {
        MBDD_T temp = *MBDDIBuffer<MBDD_T>::m_data;

        // -- Kolb line -- //

        if (MBDDIBuffer<MBDD_T>::is_link == false)
            delete MBDDIBuffer<MBDD_T>::m_data;
        std::swap(*new_data, temp);

        MBDDIBuffer<MBDD_T>::m_data = new_data;

        MBDDIBuffer<MBDD_T>::is_link = true;
    }
}

}; // namespace kusengine::render

#endif // BASE_MABDDI_HPP
