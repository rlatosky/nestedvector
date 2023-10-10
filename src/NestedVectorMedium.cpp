// Copyright 2023, Jefferson Science Associates, LLC.
// Subject to the terms in the LICENSE file found in the top-level directory.

#include <NestedVectorMedium.hpp>

NestedVectorMedium::NestedVectorMedium(size_t depth) : m_depth(depth) {
}

double NestedVectorMedium::get(const TensorIndices& indices) {
    // TODO: Implement me!
    return 0.0;
}

void NestedVectorMedium::reserve(size_t level, size_t count) {
    // TODO: Implement me!
}

void NestedVectorMedium::append(double data) {
    // TODO: Implement me!
}

size_t NestedVectorMedium::depth() {
    return m_depth;
}

size_t NestedVectorMedium::size(const TensorIndices& indices) {
    // TODO: Implement me!
    return 0;
}

