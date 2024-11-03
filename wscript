#! /usr/bin/env python3

top = "."
out = "build"
CXXFLAGS = ["-Wall", "-Werror", "-std=c++17", "-g", "-O0"]


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
            "src/Code/DayOne.cpp",
            "src/Code/CalorieParser.cpp",
        ],
        target="calorieParser",
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
            "src/Code/DayTwo.cpp",
            "src/Code/RockPaperScissors.cpp",
        ],
        target="rockPaperScissors",
        includes=["src/Include/"],
        cxxflags=CXXFLAGS,
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
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/DayThree.cpp",
            "src/Code/RucksackReorganizer.cpp",
        ],
        target="rucksack",
        includes=["src/Include/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/RucksackReorganizer.cpp",
            "src/Code/RucksackReorganizerTest.cpp",
        ],
        target="rucksackTest",
        includes=["src/Include/", "doctest/doctest/"],
        cxxflags=CXXFLAGS,
        use=["doctest"],
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/DayFour.cpp",
            "src/Code/CampCleanup.cpp",
            "src/Code/Assignment.cpp",
        ],
        target="campCleanup",
        includes=["src/Include/"],
        cxxflags=CXXFLAGS,
    )
    bld.program(
        features="cxx cxxprogram",
        source=[
            "src/Code/CampCleanup.cpp",
            "src/Code/Assignment.cpp",
            "src/Code/CampCleanupTest.cpp",
        ],
        target="campCleanupTest",
        includes=["src/Include/", "doctest/doctest/"],
        cxxflags=CXXFLAGS,
        use=["doctest"],
    )
