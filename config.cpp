#include <tuple>
#include <queue>
#include <vector>

typedef std::tuple<int, int> Location;

namespace std {
    template <> struct hash<Location> {
        typedef Location argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const Location& id) const noexcept {
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
