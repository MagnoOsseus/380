#pragma once
#include "Misc/PathfindingDetails.hpp"
#include <array>
#include <cstdint>

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */

    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */

private:
    static constexpr int MAX_MAP_WIDTH = 40;
    static constexpr int MAX_MAP_HEIGHT = 40;
    static constexpr int MAX_NODE_COUNT = MAX_MAP_WIDTH * MAX_MAP_HEIGHT;
    static constexpr std::uint16_t INVALID_NODE = 0xFFFFu;

    enum class NodeState : std::uint8_t
    {
        UNVISITED,
        ON_OPEN,
        ON_CLOSED
    };

    struct Node
    {
        float g;
        float f;
        std::uint16_t parent;
        std::int16_t heapIndex;
        std::uint8_t neighborMask;
        NodeState state;
    };

    struct SearchState
    {
        GridPos start;
        GridPos goal;
        Heuristic heuristic;
        float weight;
        std::uint16_t startIndex;
        std::uint16_t goalIndex;
        std::uint16_t openCount;
        std::uint16_t touchedCount;
        bool active;
        bool debugColoring;
    };

    std::array<Node, MAX_NODE_COUNT> nodes_{};
    std::array<std::uint16_t, MAX_NODE_COUNT> openHeap_{};
    std::array<std::uint16_t, MAX_NODE_COUNT> touched_{};
    std::array<float, MAX_NODE_COUNT> manhattanTable_{};
    std::array<float, MAX_NODE_COUNT> chebyshevTable_{};
    std::array<float, MAX_NODE_COUNT> euclideanTable_{};
    std::array<float, MAX_NODE_COUNT> octileTable_{};

    SearchState search_{};
    unsigned cachedMapIndex_{ static_cast<unsigned>(-1) };
    int mapWidth_{ 0 };
    int mapHeight_{ 0 };
    float cellWidth_{ 0.0f };
    bool lookupReady_{ false };
    bool mapReady_{ false };

    void initialize_lookup_tables();
    void preprocess_current_map();
    void on_map_change();
    std::uint16_t to_index(int row, int col) const;
    GridPos to_grid(std::uint16_t index) const;
    bool is_blocked(int row, int col) const;
    float heuristic_cost(std::uint16_t index, std::uint16_t goalIndex, Heuristic heuristic) const;
    void reset_search_state();
    void mark_touched(std::uint16_t index);
    void set_debug_color(std::uint16_t index, const Color &color) const;
    bool open_less(std::uint16_t lhs, std::uint16_t rhs) const;
    void heap_sift_up(std::uint16_t heapSlot);
    void heap_sift_down(std::uint16_t heapSlot);
    void heap_push(std::uint16_t index);
    std::uint16_t heap_pop();
    void heap_update(std::uint16_t index);
    bool has_line_of_sight(std::uint16_t fromIndex, std::uint16_t toIndex) const;
    void build_index_path(std::array<std::uint16_t, MAX_NODE_COUNT> &pathIndices, int &count) const;
    void build_output_path(PathRequest &request);
    PathResult start_search(PathRequest &request);
    PathResult step_search(PathRequest &request);
};