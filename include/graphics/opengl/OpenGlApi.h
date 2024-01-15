//
// Created by Alex on 26/12/2023.
//

#ifndef ORION_OPENGLAPI_H
#define ORION_OPENGLAPI_H

#include "GL/glew.h"

#include "core/type.h"

#include <string_view>

namespace orion {

    enum class DepthFunction {
        NEVER     = GL_NEVER,
        EQUAL     = GL_EQUAL,
        NOT_EQUAL = GL_NOTEQUAL,
        LESS      = GL_LESS,
        LE        = GL_LEQUAL,
        GREATER   = GL_GREATER,
        GE        = GL_GEQUAL,
        ALWAYS    = GL_ALWAYS
    };

    enum class EnableCapability {
        BLEND                         = GL_BLEND,
        CLIP_DISTANCE                 = GL_CLIP_DISTANCE0,
        COLOR_LOGIC_OP                = GL_COLOR_LOGIC_OP,
        CULL_FACE                     = GL_CULL_FACE,
        DEPTH_CLAMP                   = GL_DEPTH_CLAMP,
        DEBUG_OUTPUT                  = GL_DEBUG_OUTPUT,
        DEBUG_OUTPUT_SYNCHRONOUS      = GL_DEBUG_OUTPUT_SYNCHRONOUS,
        DEPTH_TEST                    = GL_DEPTH_TEST,
        DITHER                        = GL_DITHER,
        FRAMEBUFFER_SRGB              = GL_FRAMEBUFFER_SRGB,
        LINE_SMOOTH                   = GL_LINE_SMOOTH,
        MULTISAMPLE                   = GL_MULTISAMPLE,
        POLYGON_SMOOTH                = GL_POLYGON_SMOOTH,
        POLYGON_OFFSET_FILL           = GL_POLYGON_OFFSET_FILL,
        POLYGON_OFFSET_LINE           = GL_POLYGON_OFFSET_LINE,
        POLYGON_OFFSET_POINT          = GL_POLYGON_OFFSET_POINT,
        PROGRAM_POINT_SIZE            = GL_PROGRAM_POINT_SIZE,
        PRIMITIVE_RESTART             = GL_PRIMITIVE_RESTART,
        PRIMITIVE_RESTART_FIXED_INDEX = GL_PRIMITIVE_RESTART_FIXED_INDEX,
        SAMPLE_ALPHA_TO_COVERAGE      = GL_SAMPLE_ALPHA_TO_COVERAGE,
        SAMPLE_ALPHA_TO_ONE           = GL_SAMPLE_ALPHA_TO_ONE,
        SAMPLE_COVERAGE               = GL_SAMPLE_COVERAGE,
        SAMPLE_MASK                   = GL_SAMPLE_MASK,
        SCISSOR_TEST                  = GL_SCISSOR_TEST,
        STENCIL_TEST                  = GL_STENCIL_TEST,
        TEXTURE_CUBE_MAP_SEAMLESS     = GL_TEXTURE_CUBE_MAP_SEAMLESS,
    };

    enum class CullFace {
        FRONT          = GL_FRONT,
        BACK           = GL_BACK,
        FRONT_AND_BACK = GL_FRONT_AND_BACK,
    };

    enum class FrontFace {
        CLOCKWISE         = GL_CW,
        COUNTER_CLOCKWISE = GL_CCW,
    };

    class OpenGlApi {
    public:
        static bool is_loaded;

        static void load();

        static bool is_enable(EnableCapability cap);

        static void set_depth_function(DepthFunction func);
        static void set_enable        (EnableCapability cap);
        static void set_disable       (EnableCapability cap);
        static void set_cull_face     (CullFace cf);
        static void set_front_face    (FrontFace ff);
    };

#ifdef ORION_DEBUG
    #define gl_check(expr)                                      \
        do {                                                   \
            expr;                                              \
            orion::gl_check_error(__FILE__, __LINE__, #expr); \
        } while (false)
#else
    #define gl_check(expr) (expr)
#endif

    void gl_check_error(Ref<Path> file, u32 line, std::string_view expression);

} // orion

#endif //ORION_OPENGLAPI_H
