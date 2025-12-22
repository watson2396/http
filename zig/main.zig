const std = @import("std");

pub fn main() !void {
    std.debug.print("Hello, World", .{});

    var gpa_alloc = std.heap.GeneralPurposeAllocator(.{}).init;
    defer std.debug.assert(gpa_alloc.deinit() == .ok);
    const gpa = gpa_alloc.allocator();

    const address = try std.net.Address.parseIp4(&[4]u8{ 127, 0, 0, 1 }, 6969);
    var server = try address.listen(.{});

    std.log.info("server listening on port: 6969", .{});

    var client = try server.accept();
    defer .client.stream.close();

    // stream.reader needs a buffer
    const client_reader = client.stream.reader(.{});
    // stream.writer needs a buffer
    const client_writer = client.stream.writer(.{});

    while (true) {
        const msg = client_reader.readUntilDelimiterOrEofAlloc(gpa, '\n', 65536);
        defer gpa.free(msg);

        std.log.info("Recieved message: \"{}\"", .{std.zig.fmtEscapes(msg)});

        try client_writer.writeAll(msg);
    }
}
