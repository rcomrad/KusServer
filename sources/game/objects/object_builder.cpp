#include "object_builder.hpp"

#include "kernel/framework/logger/basic/exception.hpp"

#include "base_object.hpp"
#include "object_info.hpp"
#include "object_type.hpp"
#include "objects.hpp"

// namespace game::obj
// {

// } // namespace game::obj

// std::unique_ptr<BaseObject>
// game::obj::createObject(const ObjectInfo& a_obj_info)
// {
//     const int type = generateTypeMask(a_info.type);
//     switch (type)
//     {
//         case Object_CD::getType():
//             return std::make_unique<Object_CD>(a_obj_info.level,
//                                                Coordinatable(a_obj_info),
//                                                Drawable(a_obj_info));
//         case Object_CDH::getType():
//             return std::make_unique<Object_CDH>(
//                 a_obj_info.level, Coordinatable(a_obj_info),
//                 Drawable(a_obj_info), Hitable(Textable));
//         case Object_CDT::getType():
//             return std::make_unique<Object_CDT>(
//                 a_obj_info.level, Coordinatable(a_obj_info),
//                 Drawable(a_obj_info), Textable(Textable));
//         case Object_CDHT::getType():
//             return std::make_unique<Object_CDHT>(
//                 a_obj_info.level, Coordinatable(a_obj_info),
//                 Drawable(a_obj_info), Hitable(a_obj_info),
//                 Textable(Textable));
//         case Object_CT::getType():
//             return std::make_unique<Object_CT>(a_obj_info.level,
//                                                Coordinatable(a_obj_info),
//                                                Textable(Textable));
//     }
// }

std::unique_ptr<game::obj::BaseObject>
game::obj::createObject(game::obj::ObjectInfo const& a_obj_info)
{
    const int type = generateTypeMask(a_obj_info.type);
    switch (type)
    {
        case Object_CD::getType():
            return std::make_unique<Object_CD>(a_obj_info);
        case Object_CDH::getType():
            return std::make_unique<Object_CDH>(a_obj_info);
        case Object_CDT::getType():
            return std::make_unique<Object_CDT>(a_obj_info);
        case Object_CDHT::getType():
            return std::make_unique<Object_CDHT>(a_obj_info);
        case Object_CT::getType():
            return std::make_unique<Object_CT>(a_obj_info);
        default:
            THROW("Unrecognized object");
    }
}
