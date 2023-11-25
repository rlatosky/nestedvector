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
	datapoints = {};
	startindexofchildnodes = {};
}

double NestedVectorHard::get(const TensorIndices& indices) {
    // TODO: Implement me!
    size_t levelofchildnode = indices.get_index(0);
    size_t datapointofchildnode = indices.get_index(1);
									//5										1		0		= 6
    size_t requestedpartofnode = startindexofchildnodes[levelofchildnode] + 2 + datapointofchildnode; // Skip over size element
    return datapoints[tree[requestedpartofnode]];
}

void NestedVectorHard::reserve(size_t level, size_t count) {
	/* Let's remove the param level */

	/* --- First command: reserve(2) _(Tree is empty) --- */
    if (std::empty(tree)) {
        level0count = count + 2;
        tree.push_back(count);
        for (size_t i = 0; i < count + 1; i++)
            tree.push_back(0);	// includes size, and the other zeros
        return;
    }
	/* Here, reserve(2) gives us tree[] = [2,0,0,0] */

    /* --- Second command: reserve(4) --- */
    startindexofchildnodes.push_back(tree.size());	// Should say our first/second/third node is at index (size of tree at the time)
    // startindexofchildnodes[] = [4]
    tree.push_back(count);	// tree[] now should look like: [2,0,0,0,4]


    // We can say level0count + (any other counts) - 1
    for (size_t i = 0; i < count + 1; i++)
        tree.push_back(0);	// tree[] now should look like: [2,0,0,0,4,0,0,0,0,0]

    /* Now update at depth 0 */
    for (size_t i = 2; i < level0count; i++) {
		// level0count is, in the example, 4
        if (tree[i] == 0) {
        	tree[1] += 1;	// increment size element in array
            tree[i] = startindexofchildnodes[i - 2];	// tree[] = [2,1,4,0,4,0,0,0,0,0]
            break;
        }
        else {
        	std::cout << "tree[" << i << "] is full!" << std::endl;
        	continue;
        }
    }
}

void NestedVectorHard::debug() {
	int e = 0;
	int d = 0;
	int f = 0;
    std::cout << "======" << std::endl;
		std::cout << tree.size() << std::endl;
    for (size_t x : tree){
		std::cout << e++ << " element in tree: " << x << std::endl;
	}
    std::cout << "======" << std::endl;
    for (size_t y : startindexofchildnodes){
		std::cout << d++ << " element in startindexofchildnodes: " << y << std::endl;
	}
	std::cout << "======" << std::endl;
    for (double z : datapoints){
		std::cout << f++ << " element in data: " << z << std::endl;
	}
    std::cout << "======" << std::endl;
}

void NestedVectorHard::append(double data) {
	datapoints.push_back(data);	// update data array

	// Now update in any available node
	for (size_t i : startindexofchildnodes){
		if (tree[i+1] < tree[i]){
			tree[i+1] += 1;	// Update size of nested vector
			break;
		}
		else
			continue;
	}
	
	for (size_t i = 0; i < tree.size(); i++) {
		if (datapoints.size() - 1 == 0)
			return;
		else if (i > level0count + 2 ){	// Get past main node
			if (tree[i] == 0){
				tree[i] = datapoints.size() - 1;
				break;
			}
			else
				continue;
		}
	}
}

size_t NestedVectorHard::depth() {
    return m_depth;
}

size_t NestedVectorHard::size(const TensorIndices& indices) {

	if (indices.get_dim_count() == 0)
		return startindexofchildnodes.size();
	else if (indices.get_index(0) == 0)
		return tree[1];
	else
	{
		size_t requestedvector = indices.get_index(0);
		return tree[startindexofchildnodes[requestedvector]+1];
	}

}

