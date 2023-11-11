// Copyright 2023, Jefferson Science Associates, LLC.
// Subject to the terms in the LICENSE file found in the top-level directory.

#include <NestedVectorHard.hpp>

/*
 * The purpose is to set up a system where the first few numbers is at level 0.
 * The next numbers is the first node of level 1, and so on...
 * For example:
 * 
 * [3,3,5,9,14] - At lvl 0, we have a data structure of capacity 3 and size 3 with
 * the '5', '9', and '14' indicating the offset where the data is actually contained 
 * 
 *
*/

NestedVectorHard::NestedVectorHard(size_t depth) : m_depth(depth) {
	// for (size_t i : depth)
	tree = {};
	data = {};
	startindexofnode = {};
}

double NestedVectorHard::get(const TensorIndices& indices) {
    // TODO: Implement me!
    return 0.0;
}

void NestedVectorHard::reserve(size_t level, size_t count) {
	// We have to check the level - we can't call v.reserve (0, x) twice!
	if (std::empty(tree))
		level = 0;  // default to zero

	/* Let's remove the param level */
	/* First command: reserve(2) */
    if (std::empty(tree)) {
        level0count = count + 2;
        tree.push_back(count);
        for (size_t i = 0; i < count + 1; i++)
            tree.push_back(0); // includes size, and the other zeros
        return;
    }

    /* Second command: reserve(4) */
    tree.push_back(count);
    startindexofnode.push_back(std::size(tree) - 1); // Should say our first/second/third node is at index (size of tree at the time - 1)

    // We can say level0count + (any other counts) - 1
    for (size_t i = 0; i < count + 1; i++)
        tree.push_back(0);

    /* Now update at depth 0 */
    for (size_t i = 2; i < level0count; i++) {
        if (tree[i] == 0) {
            tree[i] = startindexofnode[i - 2]; return;
        }
        else {
            std::cout << "Size is full" << std::endl;
            return;
        }
    }

    // Use startindexofnode to find next available node to insert data...

}

void NestedVectorHard::append(double data) {
	
}

size_t NestedVectorHard::depth() {
    return m_depth;
}

size_t NestedVectorHard::size(const TensorIndices& indices) {
    size_t counter = 0;
    return 0;
}

