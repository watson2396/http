// const cc = b.addSystemCommand(&.{
//      "cc",
//      "-c",
//      "hello.c",
//      "-o",
//      "hello.o"
// });
// link.dependOn(&cc.step);
// const http_server = b.addStaticLibrary(.{
//     .name = "emlib",
//     .target = target,
//     .optimize = optimize,
// });
// http_server.addCSourceFiles(.{ .files = &.{"em-lib/emlib.c"} });
// http_server.addIncludePath(b.path("em-lib"));
// http_server.linkLibC();
// http_server.linkLibCpp();
// http_server.installHeader(b.path("em-lib/emlib.h"), "em-lib/emlib.h");
// b.installArtifact(http_server);

// // Linking in "emlib" to our main executable + including the header path
// exe.linkLibrary(http_server);
