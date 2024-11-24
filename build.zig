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

    const calorie = b.addExecutable(.{
        .name = "calorieParser",
        .target = b.host,
    });
    calorie.addCSourceFile(.{
        .file = b.path("src/dayone.cpp"),
        .flags = &flags,
    });
    calorie.addIncludePath(doctest);
    calorie.linkLibCpp();
    b.installArtifact(calorie);
    const run_calorie = b.addRunArtifact(calorie);
    const run_step_calorie = b.step("run-calorie", "Run the calorie parser");
    run_step_calorie.dependOn(&run_calorie.step);

    const rps = b.addExecutable(.{
        .name = "rps",
        .target = b.host,
    });
    rps.addCSourceFile(.{
        .file = b.path("src/daytwo.cpp"),
        .flags = &flags,
    });
    rps.addIncludePath(doctest);
    rps.linkLibCpp();
    b.installArtifact(rps);
    const run_rps = b.addRunArtifact(rps);
    const run_step_rps = b.step("run-rps", "Run rock paper scissors");
    run_step_rps.dependOn(&run_rps.step);

    const rucksack = b.addExecutable(.{
        .name = "rucksack",
        .target = b.host,
    });
    rucksack.addCSourceFile(.{
        .file = b.path("src/daythree.cpp"),
        .flags = &flags,
    });
    rucksack.addIncludePath(doctest);
    rucksack.linkLibCpp();
    b.installArtifact(rucksack);
    const run_rucksack = b.addRunArtifact(rucksack);
    const run_step_rucksack = b.step("run-rucksack", "Run rucksack");
    run_step_rucksack.dependOn(&run_rucksack.step);

    const camp = b.addExecutable(.{
        .name = "camp",
        .target = b.host,
    });
    camp.addCSourceFile(.{
        .file = b.path("src/dayfour.cpp"),
        .flags = &flags,
    });
    camp.addIncludePath(doctest);
    camp.linkLibCpp();
    b.installArtifact(camp);
    const run_camp = b.addRunArtifact(camp);
    const run_step_camp = b.step("run-camp", "Run Camp Cleanup");
    run_step_camp.dependOn(&run_camp.step);

    const day_five = b.addExecutable(.{
        .name = "day_five",
        .target = b.host,
    });
    day_five.addCSourceFile(.{
        .file = b.path("src/dayfive.cpp"),
        .flags = &flags,
    });
    day_five.addIncludePath(doctest);
    day_five.linkLibCpp();
    b.installArtifact(day_five);
    const run_day_five = b.addRunArtifact(day_five);
    const run_step_day_five = b.step("run-day-five", "Run Day Five");
    run_step_day_five.dependOn(&run_day_five.step);
}
