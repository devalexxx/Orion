//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGlApi.h"

#include "graphics/opengl/OpenGlContext.h"

#include <cassert>

#include <fmt/core.h>
#include <fmt/ostream.h>

namespace orion {

#ifdef ORION_DEBUG
    OpenGlCallTrace OpenGlApi::CALL_TRACE = {};
#endif

    bool OpenGlApi::IS_LOADED = false;

    void OpenGlApi::load() {

        assert(OpenGlContext::is_any_current() && "You can't load OpenGl api without OpenGl context.");

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            fmt::print(stderr, "Could not initialize OpenGL API. \n");
            exit(EXIT_FAILURE);
        }

        IS_LOADED = true;
    }

    bool OpenGlApi::is_enable(EnableCapability cap) {
        return glIsEnabled(EnumValue<EnableCapability>(cap)) == GL_TRUE;
    }

    void OpenGlApi::set_depth_function(DepthFunction func) {
        if (is_enable(EnableCapability::DEPTH_TEST))
            gl_check(glDepthFunc(EnumValue<DepthFunction>(func)));
        else
            fmt::print(stderr, "You may enable EnableCapability::DEPTH_TEST to use depth func\n");
    }

    void OpenGlApi::set_enable(EnableCapability cap) {
        if (!is_enable(cap))
            gl_check(glEnable(EnumValue<EnableCapability>(cap)));
    }

    void OpenGlApi::set_disable(EnableCapability cap) {
        if (is_enable(cap))
            gl_check(glDisable(EnumValue<EnableCapability>(cap)));
    }

    void OpenGlApi::set_cull_face(CullFace cf) {
        gl_check(glCullFace(EnumValue<CullFace>(cf)));
    }

    void OpenGlApi::set_front_face(FrontFace ff) {
        gl_check(glFrontFace(EnumValue<FrontFace>(ff)));
    }

#ifdef ORION_DEBUG

    void gl_check_error(Ref<Path> file, u32 line, std::string_view expression) {
        const GLenum errorCode = glGetError();

        if (expression.contains("Bind"))
            OpenGlApi::CALL_TRACE.bound   += 1;
        else if (expression.contains("Draw"))
            OpenGlApi::CALL_TRACE.draw    += 1;
        else if (expression.contains("UseProgram"))
            OpenGlApi::CALL_TRACE.program += 1;
        else if (expression.contains("Uniform"))
            OpenGlApi::CALL_TRACE.uniform += 1;

        if (errorCode != GL_NO_ERROR) {
            std::string error = "Unknown error";
            std::string description = "No description";

            switch (errorCode) {
                case GL_INVALID_ENUM: {
                    error = "GL_INVALID_ENUM";
                    description = "An unacceptable value has been specified for an enumerated argument.";
                    break;
                }

                case GL_INVALID_VALUE: {
                    error = "GL_INVALID_VALUE";
                    description = "A numeric argument is out of range.";
                    break;
                }

                case GL_INVALID_OPERATION: {
                    error = "GL_INVALID_OPERATION";
                    description = "The specified operation is not allowed in the current state.";
                    break;
                }
                case GL_STACK_OVERFLOW: {
                    error = "GL_STACK_OVERFLOW";
                    description = "This command would cause a stack overflow.";
                    break;
                }

                case GL_STACK_UNDERFLOW: {
                    error = "GL_STACK_UNDERFLOW";
                    description = "This command would cause a stack underflow.";
                    break;
                }

                case GL_OUT_OF_MEMORY: {
                    error = "GL_OUT_OF_MEMORY";
                    description = "There is not enough memory left to execute the command.";
                    break;
                }

                case GL_INVALID_FRAMEBUFFER_OPERATION: {
                    error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    description = "The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
                    break;
                }
                default:
                    break;
            }

            fmt::print(
                stderr,
                "An internal OpenGL call failed in {}, ({}).\nExpression:\n\t{}\nError description:\n\t{}\n{}\n",
                fmt::streamed(file.filename()), line, expression, error, description
            );
        }
    }

#endif

} // orion