const std = @import("std");
const rl = @import("raylib");

const AppState = struct {
    minutes: f32,
    seconds: f32,
    pomodoros: u32,
};
var appState = AppState{ .minutes = 25, .seconds = 0, .pomodoros = 4 };

fn clockScreen(allocator: std.mem.Allocator) anyerror!void {
    appState.seconds -= rl.getFrameTime();

    if (appState.seconds <= 0) {
        appState.seconds = 60;
        appState.minutes = appState.minutes - 1;
    }

    const minutes = try std.fmt.allocPrint(allocator, "{d}", .{@as(u32, @intFromFloat(appState.minutes))});
    const seconds = try std.fmt.allocPrint(allocator, "{d}", .{@as(u32, @intFromFloat(appState.seconds))});
    const size = rl.measureTextEx(rl.getFontDefault(), "00:00", 40, 40 / 10);
    const text_pos = rl.Vector2{
        .x = @as(f32, @floatFromInt(@divTrunc(rl.getScreenWidth(), 2))) - @divTrunc(size.x, 2),
        .y = @as(f32, @floatFromInt(@divTrunc(rl.getScreenHeight(), 2))) - @divTrunc(size.y, 2),
    };
    const slice = try std.fmt.allocPrint(allocator, "{s}:{s}\x00", .{ minutes, seconds });
    defer allocator.free(slice);
    const result = slice[0 .. slice.len - 1 :0];
    rl.drawText(result, @as(i32, @intFromFloat(text_pos.x)), @as(i32, @intFromFloat(text_pos.y)), 40, rl.Color.blue);
}

pub fn main() anyerror!void {
    const screenWidth = 800;
    const screenHeight = 450;

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    const allocator = arena.allocator();

    rl.initWindow(screenWidth, screenHeight, "animedoro");
    defer rl.closeWindow();

    rl.setTargetFPS(60);

    while (!rl.windowShouldClose()) {
        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(rl.Color.white);

        try clockScreen(allocator);
    }
}
