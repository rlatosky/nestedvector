// Copyright 2023, Jefferson Science Associates, LLC.
// Subject to the terms in the LICENSE file found in the top-level directory.

#include "TensorIndices.hpp"

class NestedVectorHard {
private:
    size_t m_depth;
    // TODO: Add data structures here!

public:
    NestedVectorHard(size_t depth);

    size_t depth();
    size_t size(const TensorIndices& indices);

    double get(const TensorIndices& indices);
    void reserve(size_t level, size_t count);
    void append(double data);
};


