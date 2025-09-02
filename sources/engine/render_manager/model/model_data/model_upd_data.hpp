#ifndef MODEL_UPD_DATA_HPP
#define MODEL_UPD_DATA_HPP
#include <memory>

namespace kusengine::render
{
class ModelUpdData
{
public:
    virtual ~ModelUpdData() = default;

    enum class Type
    {
        MATRIX4x4
    };

    Type getType() const noexcept;

    ModelUpdData(Type t);

    virtual const char* const get() const noexcept = 0;

    virtual int byteSize() const noexcept = 0;

    virtual std::unique_ptr<ModelUpdData> clone() const = 0;

    void link(char* const data) noexcept;

    void unlink() noexcept;

protected:
    virtual void resetBufData() = 0;

private:
    Type m_type;

    bool m_is_model_upd_data_linked;

    char* m_data_link;
};

} // namespace kusengine::render

#endif // MODEL_UPD_DATA_HPP
