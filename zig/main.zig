const std = @import("std");

// assumption: only making this for windows for now
// 1. connect to socket
// 2. loop over socket
// 3. read messages from socket
// 4. send message back through socket?

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

    const client_reader = client.stream.reader(&.{});
    const client_writer = client.stream.writer(&.{});

    while (true) {
        //const msg = client_reader.readUntilDelimiterOrEofAlloc(gpa, '\n', 65536);
        const msg = client_reader.net_stream;
        defer gpa.free(msg);

        std.log.info("Recieved message: \"{}\"", .{std.zig.fmtEscapes(msg)});

        try client_writer.writeAll(msg);
    }
}
