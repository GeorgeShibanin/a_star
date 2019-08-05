#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include "config.cpp"


struct Grid {

    typedef std::tuple<int, int> Location;
    int width, height;
    std::unordered_set<Location> walls;
    std::unordered_map<Location, double> weightsCords;


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

    double solve(Location loc, bool option) const {
        double res;
        if (weightsCords.find(loc) != weightsCords.end()) {
            if (option) {
                res = sqrt(2 * pow((weightsCords.find(loc)->second), 2));
            } else {
                res = weightsCords.find(loc)->second;
            }
        } else {
            if (option) {
                res = sqrt(2);
            } else {
                res = 1;
            }
        }
        return res;
    }

    double cost(Location from, Location to) const {
        double first, second;
        int a, b, c, d;
        std::tie(a, b) = from;
        std::tie(c, d) = to;
        if (std::abs(a - c) + std::abs(b - d) == 2) {
            first = solve(from, true);
            second = solve(to, true);
        } else {
            first = solve(from, false);
            second = solve(to, false);
        }
        return first + second;
    }

    std::vector<Location> neighbors(Location id) const {
        std::vector<Location> results;
        std::vector<Location> xy;
        int x, y;
        std::tie(x, y) = id;
        xy.emplace_back(std::tuple<int, int>(x + 1, y));
        xy.emplace_back(std::tuple<int, int>(x + 1, y - 1));
        xy.emplace_back(std::tuple<int, int>(x, y - 1));
        xy.emplace_back(std::tuple<int, int>(x - 1, y - 1));
        xy.emplace_back(std::tuple<int, int>(x - 1, y));
        xy.emplace_back(std::tuple<int, int>(x - 1, y + 1));
        xy.emplace_back(std::tuple<int, int>(x, y + 1));
        xy.emplace_back(std::tuple<int, int>(x + 1, y + 1));
        for (auto i : xy) {
            if (in_bounds(i) && passable(i)) {
                results.push_back(i);
            }
        }
        return results;
    }
};

