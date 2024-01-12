//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGlApi.h"

#include <iostream>
#include <cassert>

#include "graphics/opengl/OpenGlContext.h"

namespace orion {

    bool OpenGlApi::is_loaded = false;

    void OpenGlApi::load() {

        assert(OpenGlContext::is_any_current() && "You can't load OpenGl api without OpenGl context.");

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize OpenGL API. \n";
            exit(EXIT_FAILURE);
        }

        is_loaded = true;
    }

    bool OpenGlApi::is_enable(EnableCapability cap) {
        return glIsEnabled(std::underlying_type<EnableCapability>::type(cap)) == GL_TRUE;
    }

    void OpenGlApi::set_depth_function(DepthFunction func) {
        if (is_enable(EnableCapability::DEPTH_TEST))
            gl_check(glDepthFunc(std::underlying_type<DepthFunction>::type(func)));
        else
            std::cerr << "You may enable EnableCapability::DEPTH_TEST to use depth func\n";
    }

    void OpenGlApi::set_enable(EnableCapability cap) {
        if (!is_enable(cap))
            gl_check(glEnable(std::underlying_type<EnableCapability>::type(cap)));
    }

    void OpenGlApi::set_disable(EnableCapability cap) {
        if (is_enable(cap))
            gl_check(glDisable(std::underlying_type<EnableCapability>::type(cap)));
    }

    void gl_check_error(Ref<Path> file, u32 line, std::string_view expression) {
        const GLenum errorCode = glGetError();

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

            std::cerr << "An internal OpenGL call failed in " << file.filename() << "(" << line << ")."
                  << "\nExpression:\n   " << expression << "\nError description:\n   " << error << "\n   "
                  << description << '\n';
        }
    }
} // orion