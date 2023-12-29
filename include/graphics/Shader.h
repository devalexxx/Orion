//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_SHADER_H
#define ORION_SHADER_H

#include <string>
#include <unordered_map>

#include "core.h"
#include "math/Matrix4.h"

namespace orion {
class Shader : public std::enable_shared_from_this<Shader> {

        enum class Type {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
        };

    public:
        static DeferredRegistry<Shader> REGISTRY;

        static std::shared_ptr<Shader> load_from_file(Ptr<char> vertex, Ptr<char> fragment);
        static std::shared_ptr<Shader> load_from_code(Ref<std::string> vertex, Ref<std::string> fragment);

        static void unbind();

        ~Shader();

        void use() const;

        bool has_attrib (Ptr<char> name) const;
        bool has_uniform(Ptr<char> name) const;

        int get_uniform_location(Ptr<char> name) const;
        int get_attrib_location (Ptr<char> name) const;

        void set_uniform(Ptr<char> name, int value)           const;
        void set_uniform(Ptr<char> name, Ref<Matrix4f> value) const;

        void set_float_attrib_pointer(Ptr<char> name, u32 size, u32 stride, u32 offset) const;

    private:
        explicit Shader(Ref<std::string> vertex, Ref<std::string> fragment);

        static void handle_compile_error(u32 id);
        static void handle_link_error   (u32 id);

        void compute_mapping(Ref<std::string> code, Type type);
//        void handle_uniform_name_and_type_error(const std::string& name, const std::string& type) const;

        u32 m_id {};

        std::unordered_map<std::string, std::string> m_attrib   {};
        std::unordered_map<std::string, std::string> m_uniform {};
    };
}


#endif //ORION_SHADER_H
