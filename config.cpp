#include <tuple>
#include <queue>
#include <vector>

struct Node
{
    std::tuple<int, int> xy;
    double  f, g, h;
    double weights;

    bool operator== (const Node &other) const {
        int a, b, c, d;
        std::tie(a, b) = this->xy;
        std::tie(c, d) = other.xy;
        return a == c && b == d;
    }
};

namespace std {
    template <> struct hash<std::tuple<int, int>> {
        typedef std::tuple<int, int> argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const std::tuple<int ,int>& id) const noexcept {
            int x, y;
            std::tie(x, y) = id;
            return std::hash<int>()(x ^ (y << 4));
        }
    };
}

template<typename T, typename prior>
struct PriorityQueue {
    typedef std::pair<prior, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    bool empty() const {
        return elements.empty();
    }

    void put(T item, prior priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return  best_item;
    }
};
