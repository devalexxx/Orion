set_languages("c99", "c++23")

add_requires("glm", "doctest", "glfw")

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
        packages     = {"glm", "glfw"},
    },
    serializer = {
        config_name  = "serializer",
        dependencies = {"core"},
        packages     = {},
    }
}

target("orion")
    set_kind("static")
    add_files("src/**/*.cpp")
    add_includedirs("include", {public = true})
    add_packages("glm", {public = true})
    add_packages("glfw", {public = true})
target_end()

target("test")
    set_kind("binary")
    add_deps("orion")
    add_files("test/*.cpp")
    add_files("test/**/*.cpp")
    add_packages("doctest")
target_end()