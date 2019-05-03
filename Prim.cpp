// Prim algorithm of finding minimal spanning tree (using binary heap) 
#include <vector>
#include <iostream>
#include <set>
#include <map>

const int long_distance = 100000000;

template <typename T, typename Key>
void Heapify_Up(std::vector<std::pair<Key, T>>& heap, size_t index) {
    while (index > 1 && heap[index - 1].second < heap[index / 2 - 1].second) {
        std::swap(heap[index - 1], heap[index / 2 - 1]);
        index = index / 2;
    }
}

template <typename T, typename Key>
void Insert(std::vector<std::pair<Key, T>>& heap, const std::pair<Key, T> element) {
    heap.push_back(element);
    Heapify_Up(heap, heap.size());
}

template <typename T, typename Key>
void Decrease_Key(std::vector<std::pair<Key, T>>& heap, size_t& index, T value) {
    heap[index - 1].second = value;
    Heapify_Up(heap, index);
}

template <typename T, typename Key>
void Heapify_Down(std::vector<std::pair<Key, T>>& heap, const size_t& index) {
    size_t l = 2 * index;
    size_t r = l + 1;
    if (l <= heap.size()) {
        size_t child;
        if (r <= heap.size() && heap[r - 1].second < heap[l - 1].second) {
            child = r;
        } else {
            child = l;
        }
        if (heap[index - 1].second > heap[child - 1].second) {
            std::swap(heap[index - 1], heap[child - 1]);
            Heapify_Down(heap, child);
        }
    }
}

template <typename T, typename Key>
std::pair<Key, T> Extract_Min(std::vector<std::pair<Key, T>>& heap) {
    std::pair<Key, T> min_elem = heap[0];
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.erase(--(heap.end()));
    Heapify_Down(heap, 1);
    return min_elem;
}


int main() {
    int n, m, from, to, weight, answer = 0;
    std::map<std::pair<int, int>, int> w; // веса. Для порядка считаем, что в паре (x, y) x <= y
    std::vector<std::vector<int>> graph;
    std::vector<std::pair<int, int>> heap; // первый инт -- номер ребра, второй -- удаленность
    std::cin >> n >> m;
    heap.reserve(n);
    graph.reserve(n);
    std::set<int> in_heap;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        graph[to - 1].emplace_back(from - 1);
        graph[from - 1].emplace_back(to - 1);
        w[std::make_pair(std::min(from, to) - 1, std::max(from, to) - 1)] = weight;
    }
    std::vector<int> values(n), p(n);
    for (size_t i = 0; i < n; ++i) {
        values[i] = long_distance;
        if (i == 0)
            values[i] = 0;
        p[i] = -1;
        auto pr = std::make_pair(i, values[i]);
        heap.emplace_back(i, values[i]);
        in_heap.insert(i);
    }
    while (!heap.empty()) {
        auto cur_min = Extract_Min(heap);
        if (cur_min.second == values[cur_min.first]) {
            answer += w[{std::min(cur_min.first, p[cur_min.first]), std::max(cur_min.first, p[cur_min.first])}];
            in_heap.erase(cur_min.first);
            for (auto& vertex: graph[cur_min.first]) {
                if (values[vertex] > w[{std::min(vertex, cur_min.first), std::max(vertex, cur_min.first)}] && in_heap.count(vertex)) {
                    values[vertex] = w[{std::min(vertex, cur_min.first), std::max(vertex, cur_min.first)}];
                    p[vertex] = cur_min.first;
                    Insert(heap, std::make_pair(vertex, values[vertex]));
                }
            }
        }
    }
    std::cout << answer << '\n';
}

