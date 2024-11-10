#! /usr/bin/env python3

top = "."
out = "build"
CXXFLAGS = ["-Wall", "-Werror", "-std=c++17", "-g", "-O0", "-ferror-limit=0"]


def options(opt):
    opt.load(["clangxx", "clang_compilation_database"])


def configure(conf):
    conf.load(["clangxx", "clang_compilation_database"])
    conf.check(features="cxx", msg="Check for c++ features")
    conf.env.CXXFLAGS = CXXFLAGS


def build(bld):
    bld.stlib(
        source="./doctest/doctest/parts/doctest.cpp",
        features="cxx",
        target="doctest",
    )
    bld.program(
        features="cxx",
        source=[
            "src/Code/DayOne.cpp",
        ],
        target="calorieParser",
        includes=["doctest/doctest/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx",
        source=[
            "src/Code/DayTwo.cpp",
        ],
        target="rockPaperScissors",
        includes=["doctest/doctest/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx",
        source=[
            "src/Code/DayThree.cpp",
        ],
        target="rucksack",
        includes=["doctest/doctest/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx",
        source=[
            "src/Code/DayFour.cpp",
        ],
        target="campCleanup",
        includes=["doctest/doctest/"],
        cxxflags=CXXFLAGS,
    )
