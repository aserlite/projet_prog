#include "flow_field.hpp"
#include <queue>
#include <limits>

std::vector<std::vector<std::pair<int, int>>> computeFlowField(const TileMap& map, int destX, int destY) {
    int w = map.getWidth();
    int h = map.getHeight();
    std::vector<std::vector<std::pair<int, int>>> field(h, std::vector<std::pair<int, int>>(w, {destX, destY}));
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
    std::queue<std::pair<int, int>> q;

    q.push({destX, destY});
    visited[destY][destX] = true;

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !visited[ny][nx]) {
                TileType t = map.getTile(nx, ny).getType();
                if (t == TileType::Empty || t == TileType::Object) {
                    field[ny][nx] = {x, y};
                    visited[ny][nx] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
    return field;
}