add_rules("mode.debug", "mode.release")

set_languages("c99", "c++23")

add_requires("glm", "doctest", "fmt", "stb")

add_requires("glfw", {configs = { debug = is_mode("debug") }})
add_requires("glew", {configs = { debug = is_mode("debug") }})

local module = {
    core = {
        config_name  = "core",
        dependencies = {},
        packages     = {},
    },
    engine = {
        config_name  = "engine",
        dependencies = {"core"},
        packages     = {},
    },
    graphics = {
        config_name  = "graphics",
        dependencies = {"core"},
        packages     = {"glm", "glfw", "glew"},
    },
    serializer = {
        config_name  = "serializer",
        dependencies = {"core"},
        packages     = {},
    }
}

includes("xmake/**.lua")

target("orion")
    set_kind("static")
    if is_mode("debug") then
        add_defines("DEBUG")
    end
    add_files("src/**/*.cpp")
    add_includedirs("include", {public = true})
    add_packages("glm", {public = true})
    add_packages("glfw", {public = true})
    add_packages("glew", {public = true})
    add_packages("fmt", {public = true})
    add_packages("stb", {public = true})

    add_rules("glsl", "texture")

    add_files("resource/**/*.glsl")
    add_files("resource/**/*.png")
target_end()

target("test")
    set_kind("binary")
    if is_mode("debug") then
        add_defines("DEBUG")
    end
    add_deps("orion")
    add_files("test/*.cpp")
    add_files("test/**/*.cpp")
    add_packages("doctest")
target_end()