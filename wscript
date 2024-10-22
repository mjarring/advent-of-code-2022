#! /usr/bin/env python3

top = "."
out = "build"
CXXFLAGS = ["-Wall", "-Werror", "-std=c++17"]


def options(opt):
    opt.load("clangxx")


def configure(conf):
    conf.load("clangxx")
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
        source="src/main.cpp",
        target="calories",
        cxxflags=CXXFLAGS,
        use=["doctest"],
    )
