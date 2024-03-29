#include <iostream>
#include <list>
#include "structures.cpp"

/*Heuristic func*/
double h(Location x, Location y) {
    int a, b, c, d;
    std::tie(a, b) = x;
    std::tie(c, d) = y;
    return std::max(std::abs(a - c), std::abs(b - d));
}

template <typename T>
void show_me_path(T start, T goal, std::unordered_map<T, T>& came_from) {
    std::vector<T> path;
    T current = goal;
    path.push_back(current);
    while (current != start) {
        current = came_from[current];
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    std::cout << "WAY:" << "\n";
    for (auto i : path) {
        int x, y;
        std::tie(x, y) = i;
        std::cout << x << " " << y << "\n";
    }
}

/*Search algorithm*/
template<typename Graph, typename Location>
void a_star(Graph graph,
            Location start, Location goal) {
    PriorityQueue<Location, double> open;
    open.put(start, h(start, goal));
    std::unordered_map<Location, double> g;
    std::unordered_map<Location, Location> parent;
    parent[start] = start;
    g[start] = 0;
    while(!open.empty()) {
        auto current = open.get();
        int x, y;
        std::tie(x,y) = current;
        std::cout <<"\n" <<  "Visiting - " << x << " " << y;
        if (current == goal) {
            std::cout << "\n" << "FINISH" << "\n";
            show_me_path(start, goal, parent);
            break;
        }
        for (auto next :  graph.neighbors(current)) {
            double  new_cost = g[current] + graph.cost(current, next);
            if (g.find(next) == g.end() || new_cost < g[next]) {
                g[next] = new_cost;
                double f = g[next] + h(next, goal);
                parent[next] = current;
                open.put(next, f);
            }
        }
    }
}


int main() {

    /*test for grid*/

    Grid example_graph(4, 4);

    /*initialize walls*/
    std::unordered_set<Location> walls{{1,0}, {0, 1},
                                                   {2, 1}, {1, 2},
                                                   {3, 2}};
    example_graph.walls = walls;

    /*initialize cell with weights*/
    example_graph.weightsCords = {{{0,0},3}, {{1,1}, 9}, {{2, 2}, 100}, {{3, 3}, 5}};


    Location start, goal;
    start = {0, 0};
    goal = {3, 3};

    a_star(example_graph, start, goal);
}
