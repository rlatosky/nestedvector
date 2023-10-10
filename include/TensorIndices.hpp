// Copyright 2023, Jefferson Science Associates, LLC.
// Subject to the terms in the LICENSE file found in the top-level directory.
//
#include <vector>


class TensorIndices {
private:
    std::vector<size_t> m_data;
    // TODO: This will be inefficient because it will do an allocation every time a TensorIndices object gets constructed.
    //       We may want to optimize this by storing the indices to a small array whenever they fit, and to the vector otherwise.

public:
    inline TensorIndices(std::initializer_list<size_t> indices) : m_data(indices) {};
    inline TensorIndices(std::vector<size_t> indices) : m_data(indices) {};

    inline size_t get_dim_count() const { return m_data.size(); }
    inline size_t get_index(size_t dim) const { return m_data[dim]; }
    inline void set_index(size_t dim, size_t index) { m_data[dim] = index; }
};


