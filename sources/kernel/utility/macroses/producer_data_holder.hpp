#pragma once

template <typename DataType>
class ProducerDataHolder
{
public:
    ProducerDataHolder(const DataType& a_data) : m_data(a_data)
    {
    }

    DataType& get()
    {
        return m_data;
    }

private:
    DataType m_data;
};
