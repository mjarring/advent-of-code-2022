#! /usr/bin/env python3

top = "."
out = "build"
CXXFLAGS = ["-Wall", "-Werror", "-std=c++17"]


def options(opt):
    opt.load(["clangxx", "clang_compilation_database"])


def configure(conf):
    conf.load(["clangxx", "clang_compilation_database"])
    conf.check(features="cxx cxxprogram", msg="Check for c++ features")
    conf.env.CXXFLAGS = CXXFLAGS


def build(bld):
    bld.stlib(
        source="./doctest/doctest/parts/doctest.cpp",
        features="cxx",
        target="doctest",
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/Main.cpp",
            "src/Code/CalorieParser.cpp",
            "src/Code/RockPaperScissors.cpp",
        ],
        target="advent",
        includes=["src/Include/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/CalorieParser.cpp",
            "src/Code/CalorieParserTest.cpp",
        ],
        target="calorieTest",
        includes=["src/Include/", "doctest/doctest/"],
        cxxflags=CXXFLAGS,
        use=["doctest"],
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/RockPaperScissors.cpp",
            "src/Code/RockPaperScissorsTest.cpp",
        ],
        target="rockPaperScissorsTest",
        includes=["src/Include/", "doctest/doctest/"],
        cxxflags=CXXFLAGS,
        use=["doctest"],
    )
