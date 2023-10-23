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
	tree = []
	data = []
	startindexofnode = []
}

double NestedVectorHard::get(const TensorIndices& indices) {
    // TODO: Implement me!
    return 0.0;
}

void NestedVectorHard::reserve(size_t level, size_t count) {
	// We have to check the level - we can't call v.reserve (0, x) twice!
	if (tree.size().empty())
		level = 0;  // default to zero

	/* Let's remove the param level */
	/* First command: reserve(2) */
    if (tree.size().empty) {
        level0count = count + 2;
        tree.push_back(count);
        for (auto i : count + 1)
            tree.push_back(0);
    }

    /* Second command: reserve(4) */
    tree.push_back(count);
    startindexofnode.push_back(std::size(tree) - 1) // Should say our first/second/third node is at index (size of tree at the time - 1)
    for (auto i: count + 1) // We can say level0count + (any other counts) - 1
        tree.push_back(0);

    /* Now update at depth 0 */
    for (size_t i = 2; i < level0count; i++) {
        if (tree[i] == 0)
            tree[i] = startindexofnode; // This will only work at the first node
            return;
        else
            std::cout << "Size is full" << std::endl;
            return;
    }

	/*
	 * First, we iterate over depth (let's say 2)
	 * 
	 * The first time through (at depth = 0) we first push the count as index 0 of the tree vector
	 * and then push back however many zeros we need to allocate due to the count (we remember size is zero)
	 * 
	 * */
	
	if ( ((level - 0) | (m_depth - level)) >= 0 ) // Check if level is between 0 and m_depth (fast method)
		tree.push_back(count);	// set first number of node (capacity)
		for (auto i : count + 1)
			tree.push_back(0); // initialize it with a whole lotta zeros
			
	// Check if level matches with m_depth
	if ( (level >= 0) && (level <= (m_depth - 1)) ) // Check if level is between 0 and m_depth (slower method)
		tree.push_back(count);	// set first number of node (capacity)
		for (auto i : count + 1)
			tree.push_back(0); // initialize it with a whole lotta zeros
			
	/* Should look like this (if m_depth is 2, and count is 3):
	 * 
	 * FIRST ITERATION (i = 0)
	 * for (auto i: 2) {
	 * 		tree.push_back(3); first num is capacity so good
	 * 		for (auto i : 4)
	 * 			tree.push_back(0);
	 * SECOND ITERATION (i = 1)
	 * for (auto i: 2) {
	 * 		tree.push_back(3); first num is capacity so good
	 * 		for (auto i : 4)
	 * 			tree.push_back(0);
	*/
	
}

void NestedVectorHard::append(double data) {
	
}

size_t NestedVectorHard::depth() {
    return m_depth;
}

size_t NestedVectorHard::size(const TensorIndices& indices) {
    // TODO: Implement me!
    return 0;
}

