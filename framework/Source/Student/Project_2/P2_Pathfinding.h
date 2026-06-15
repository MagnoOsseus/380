#pragma once
#include "Misc/PathfindingDetails.hpp"
#include <array>
#include <cstdint>
#include <limits>

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
    // map limits
    static constexpr int MAX_MAP_WIDTH = 40;
    static constexpr int MAX_MAP_HEIGHT = 40;
    static constexpr int MAX_NODE_COUNT = MAX_MAP_WIDTH * MAX_MAP_HEIGHT;
    static constexpr std::uint16_t INVALID_NODE = std::numeric_limits<std::uint16_t>::max();
    static constexpr unsigned INVALID_MAP_INDEX = std::numeric_limits<unsigned>::max();

    // node state
    enum class NodeState : std::uint8_t
    {
        UNVISITED,
        ON_OPEN,
        ON_CLOSED
    };

    // Stores path costs and cached neighbor links.
    struct Node
    {
        float g;
        float f;
        std::uint16_t parent;
        std::int16_t heapIndex;
        bool neighbors[8];
        NodeState state;
    };

    // current search data
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

    // main cache
    std::array<Node, MAX_NODE_COUNT> nodes_{};
    std::array<std::uint16_t, MAX_NODE_COUNT> openHeap_{};
    std::array<std::uint16_t, MAX_NODE_COUNT> touched_{};
    std::array<float, MAX_NODE_COUNT> manhattanTable_{};
    std::array<float, MAX_NODE_COUNT> chebyshevTable_{};
    std::array<float, MAX_NODE_COUNT> euclideanTable_{};
    std::array<float, MAX_NODE_COUNT> octileTable_{};

    // Stores the active request while the search is running.
    SearchState search_{};
    // Tracks which map the cached graph belongs to.
    unsigned cachedMapIndex_{ INVALID_MAP_INDEX };
    // Store the current map dimensions.
    int mapWidth_{ 0 };
    int mapHeight_{ 0 };
    // Sets point spacing used for smoothing.
    float cellWidth_{ 0.0f };
    // Marks whether heuristic tables were already built.
    bool lookupReady_{ false };
    // Marks whether the map graph is ready to use.
    bool mapReady_{ false };

    // Fills the heuristic lookup tables once.
    void initialize_lookup_tables();
    // Builds the cached node graph for the current map.
    void preprocess_current_map();
    // Invalidates cached data when the map changes.
    void on_map_change();
    // Converts a grid cell into a flat array index.
    std::uint16_t to_index(int row, int col) const;
    // Converts a flat array index back into grid coordinates.
    GridPos to_grid(std::uint16_t index) const;
    // Checks whether a grid cell is outside the map or blocked.
    bool is_blocked(int row, int col) const;
    // Returns the selected heuristic value for one node.
    float heuristic_cost(std::uint16_t index, std::uint16_t goalIndex, Heuristic heuristic) const;
    // Clears the nodes touched by the current search.
    void reset_search_state();
    // Records nodes that must be reset later.
    void mark_touched(std::uint16_t index);
    // Colors cells only when debug drawing is enabled.
    void set_debug_color(std::uint16_t index, const Color &color) const;
    // Compares two open nodes using the heap ordering.
    bool open_less(std::uint16_t lhs, std::uint16_t rhs) const;
    // Restores heap order upward after an insertion.
    void heap_sift_up(std::uint16_t heapSlot);
    // Restores heap order downward after a removal.
    void heap_sift_down(std::uint16_t heapSlot);
    // Inserts one node into the open heap.
    void heap_push(std::uint16_t index);
    // Removes the best node from the open heap.
    std::uint16_t heap_pop();
    // Refreshes a node position after its score improves.
    void heap_update(std::uint16_t index);
    // Checks whether two nodes can be connected directly.
    bool has_line_of_sight(std::uint16_t fromIndex, std::uint16_t toIndex) const;
    // Rebuilds the raw node path by following parents.
    void build_index_path(std::array<std::uint16_t, MAX_NODE_COUNT> &pathIndices, int &count) const;
    // Converts the node path into final world points.
    void build_output_path(PathRequest &request);
    // Validates the request and creates the first open node.
    PathResult start_search(PathRequest &request);
    // Advances the search by expanding one node.
    PathResult step_search(PathRequest &request);
};