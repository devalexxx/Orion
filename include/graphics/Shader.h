//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_SHADER_H
#define ORION_SHADER_H

#include <string>
#include <unordered_map>

#include "core.h"
#include "math/Matrix4.h"

#include "opengl/OpenGlContextRequired.h"

namespace orion {

    class Color;

    class Shader : public OpenGlContextRequired {

        enum class Type {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
        };

    public:
        static DeferredRegistry<Shader> REGISTRY;

        static u32 CURRENT_USE;

        static std::shared_ptr<Shader> load_from_file(Ptr<char> vertex, Ptr<char> fragment);
        static std::shared_ptr<Shader> load_from_file(Ref<Path> vertex, Ref<Path> fragment);
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
        void set_uniform(Ptr<char> name, Ref<Color> value)    const;

        void set_float_attrib_pointer(Ptr<char> name, u32 size, u32 stride, u32 offset) const;

    private:
        explicit Shader(Ref<std::string> vertex, Ref<std::string> fragment);

        static void handle_compile_error(u32 id);
        static void handle_link_error   (u32 id);

        void compute_mapping(Ref<std::string> code, Type type);

        u32 m_id {};

        std::unordered_map<std::string, std::string> m_attrib  {};
        std::unordered_map<std::string, std::string> m_uniform {};

//        struct Description {
//            String type;
//            i32    location = -1;
//        };
//
//        std::unordered_map<std::string, Description> m_attrib  {};
//        std::unordered_map<std::string, Description> m_uniform {};
    };
}


#endif //ORION_SHADER_H
