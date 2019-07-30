#include <iostream>
#include "structures.cpp"

/*Heuristic func*/
double h(std::tuple<int, int> x, std::tuple<int, int> y) {
    int a, b, c, d;
    std::tie(a, b) = x;
    std::tie(c, d) = y;
    return std::abs(a - c) + std::abs(b - d);
}

/*Search algorithm*/
template<typename Graph, typename Location>
void a_star(Graph graph,
            Location start, Location goal,
            std::unordered_map<Location, Location>& came_from,
            std::unordered_map<Location, double>& cost_so_far) {
    PriorityQueue<Location, double> open;
    open.put(start, h(start, goal));
    came_from[start] = start;
    cost_so_far[start] = 0;
    while(!open.empty()) {
        auto current = open.get();
        int x, y;
        std::tie(x,y) = current;
        std::cout << "Visiting " << x << " " << y << "\n";
        if (current == goal) {
            std::cout << "u reach your goal" << "\n";
            break;
        }
        for (auto next :  graph.neighbors(current)) {
            double  new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double f = new_cost + h(next, goal);
                came_from[next] = current;
                open.put(next, f);
            }
        }
    }
}

template <typename T>
std::vector<T> show_me_path(T start, T goal, std::unordered_map<T, T>& came_from) {
    std::vector<T> path;
    T current = goal;
    path.push_back(current);
    while (current != start) {
        current = came_from[current];
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}


int main() {

    /*test for grid*/

    Grid example_graph(4, 4);

    /*initialize walls*/
    std::unordered_set<std::tuple<int, int>> walls{{1,1}, {2, 2}};
    example_graph.walls = walls;


    /*initialize cell with weights*/
    example_graph.weightsCords = {{1,2}, {2, 3}};

    std::tuple<int, int> start{0, 0};
    std::tuple<int ,int> goal{3, 3};
    std::unordered_map<std::tuple<int ,int>, std::tuple<int ,int>> came_from;
    std::unordered_map<std::tuple<int ,int>, double> cost_so_far;

    a_star(example_graph, start, goal, came_from, cost_so_far);

    /*way to the point*/
    auto way = show_me_path(start, goal, came_from);
    std::cout << "ur steps" << "\n";
    for (auto i : way) {
        int x, y;
        std::tie(x, y) = i;
        std::cout << x << " " << y << "\n";
    }
}
