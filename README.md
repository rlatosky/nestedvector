


# Nested Vector Experiments

## Background

A `std::vector` combines the best parts of an array and a list:

- It is efficient to append (`push_back`) to the *end* of the vector (~O(1))
- It is efficient to access data already in the vector given an index (~O(1))
- The data in the vector is stored densely
- No allocations are needed after the vector is created (except when the vector needs to be resized, which can be avoided if you know the final size ahead of time using `reserve`)

In exchange (there are always tradeoffs!):
- It is inefficient to insert data somewhere in the middle of the vector
- I'm sure there are more, I'm just not thinking of them


For our PHASM project, we want to create a new data structure called a *nested vector*. A nested vector behaves like a series of nested `std::vector<T>`, i.e. 
```c++
std::vector<std::vector<std::vector<T>>> v;
```
with the added benefit of being able to access its contents using a single index:

```c++
NestedVector<double> v;

// Pretend we have inserted data so that v contains [[7.7,1.9,8],[100.1,0.8],[3.141592]]
// See below for example how

double d = v.get({1,1});
REQUIRE(d == 0.8);
```

We want to keep all of the desired properties listed above. Appending to the end and accessing data should be cheap. Specifically, it should be proportional to the nesting depth, NOT proportional to the length of any individual vectors.
Most importantly, the data should all fit in a single buffer, and not use any allocations. This is why we can't just use a `std::vector<std::vector<...>>` internally! You will have to come up with a schema for organizing 
memory at a low level, very carefully.

For simplicity, we are willing to make a few extra tradeoffs to make this happen.
- There will be NO ability to insert data anywhere except at the very back 
- You know the size of each vector at each nesting level ahead of time. 
- You can pretend that the nested vector's enclosed data is always of type `double`. (This is just so that you don't have to worry about writing templates just yet!)

To populate this nested vector, I expect it'll look something like this:

```c++
NestedVector v(2);  // This example (same as above) has just two nesting levels

v.reserve(0, 3); // Reserve space for three items at the outer level
v.reserve(1, 3); // Reserve space for three items at the next slot in the inner level

v.append(7.7); 
v.append(1.9);
v.append(8);

v.reserve(1,2); // Reserve space for two items at the next slot in the inner level

v.append(100.1);
v.append(0.8);

v.reserve(1,1); // Reserve space for one item at the next slot in the inner level
v.append(3.141592);
```

One thing that really helps is to visualize this as a tree!


## Approaches

I've come up with three different approaches that will probably work. There are almost certainly more, and this is a great opportunity to be creative! 

### Easy
Don't bother tracking nesting level explicitly. Instead, simply maintain a `std::unordered_map<TensorIndex, T>` inside your `NestedVector` and use that for your lookup.
The hard part here is making sure that the indexes are valid, i.e. they describe a valid nested vector. Here is python-ish pseudocode describing the representation for 
the example above:
```python
contents = { (0,0):7.7, (0,1):1.9, (0,2):8, (1,0):100.1, (1,1):0.8, (2,0):3.141592 }
```
Here is an invalid example because the indices are not adjacent:
```c++ 
{ (0,0):7.7, (0,2):1.9}
```


### Medium
Don't bother tracking nesting level explicitly. Instead, maintain two vectors internally, one containing indices, and the other containing the corresponding data. Perform a binary
search on the vector of indices to figure out the location of the data. An example:

```python
indices = [(0,0), (0,1), (0,2), (1,0), (1,1), (2,0)]
data = [7.7, 1.9, 8, 100.1, 0.8, 3.141592]
```

### Hard
Maintain the nesting structure explicitly. Maintain an array of offsets describing the nesting, and a separate array describing the data (which only lives at the leaves). 

```python
TreeNode = ( capacity, size, offset_of_child_0, ..., offset_of_child_n, contents_of_child_0, ... , contents_of_child_n )
```

Here is our example:
```python
tree = [3, 3, 5, 9, 14, 3, 3, 0, 1, 2, 2, 2, 3, 4, 1, 1, 5 ]
data = [7.7, 1.9, 8, 100.1, 0.8, 3.141592]
```

To help understand this:

```
tree = [3, 3, 5, 9, 14, 3, 3, 0, 1, 2, 2, 2, 3, 4, 1, 1, 5 ]
              |  |  |   ^           ^              ^          
              +---------+           |              |          
                 +------------------+              |                           
                    +------------------------------+

data = [7.7, 1.9, 8, 100.1, 0.8, 3.141592]
         |    |   |   |      |    |
         \    \    \  \      \     \
           ---------------------------------------------                  
                             \   \  \        \  \        \
                              |  |  |        |  |        |
tree = [3, 3, 5, 9, 14, 3, 3, 0, 1, 2, 2, 2, 3, 4, 1, 1, 5 ]

```

Here I add parenthesis to help you reason about how we lay out data recursively:
```
tree = (3, 3, 5, 9, 14, (3, 3, 0, 1, 2), (2, 2, 3, 4), (1, 1, 5))
```






