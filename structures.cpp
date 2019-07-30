#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "config.cpp"


struct Grid {

    typedef std::tuple<int, int> Location;
    int width, height;
    std::unordered_set<Location> walls;
    std::unordered_set<Location> weightsCords;


    Grid(int width, int height): width(width), height(height) {}

    bool in_bounds(Location id) const {
        int x, y;
        std::tie(x, y) = id;
        return 0 <= x && x < width
               && 0 <= y && y < height;
    }

    bool passable(Location id) const {
        return !walls.count(id);
    }

    double cost(Location from, Location to) const {
        return weightsCords.find(to) != weightsCords.end()? 3 : 1;
    }

    std::vector<Location> neighbors(Location id) const {
        std::vector<Location> results;
        std::vector<Location> xy;
        int x, y;
        std::tie(x, y) = id;
        xy.emplace_back(Location(x + 1, y));
        xy.emplace_back(Location(x + 1, y - 1));
        xy.emplace_back(Location(x, y - 1));
        xy.emplace_back(Location(x - 1, y - 1));
        xy.emplace_back(Location(x - 1, y));
        xy.emplace_back(Location(x - 1, y + 1));
        xy.emplace_back(Location(x, y + 1));
        xy.emplace_back(Location(x + 1, y + 1));
        for (auto i : xy) {
            if (in_bounds(i) && passable(i)) {
                results.push_back(i);
            }
        }
        return results;
    }
};

