const std = @import("std");

pub fn build(b: *std.Build) void {
    const flags = [_][]const u8{
        "-Wall",
        "-Werror",
        "-std=c++17",
        "-ferror-limit=0",
        "-fno-exceptions",
    };
    const doctest = b.path("doctest/doctest");

    const advent = b.addExecutable(.{
        .name = "advent",
        .target = b.host,
    });
    advent.addCSourceFile(.{
        .file = b.path("src/advent.cpp"),
        .flags = &flags,
    });
    advent.addIncludePath(doctest);
    advent.linkLibCpp();
    b.installArtifact(advent);
    const run_advent = b.addRunArtifact(advent);
    const run_step_advent = b.step("run", "Run the application");
    run_step_advent.dependOn(&run_advent.step);
}
