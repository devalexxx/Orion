package("orion")
    set_description("Orion game engine")
    set_license("MIT")

    add_urls("https://github.com/alspin8/Orion.git")
    add_versions("0.0.1", "<shasum256 or gitcommit>")

target("orion")
    set_kind("static")
    add_files("src/library.cpp")

target("test")
    set_kind("binary")
    add_deps("orion")
    add_files("test/main.cpp")