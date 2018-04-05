#pragma once
#include <memory>
#include "ring.h"

template <typename Key, typename Info>
class Ring<Key, Info>::iterator
{
    //private member types
    mutable Node *it;

public:
    //constructors
    iterator(Node *node) noexcept : it(node)
    {}
    iterator(const_iterator& source) noexcept{
        *this = source;
    }
    iterator(iterator&& source) noexcept : it(std::move(source.it)){
        source.it = nullptr;
    }

    //operators
    iterator& operator=(const_iterator& rhs) noexcept;
    iterator& operator=(iterator&& rhs) noexcept;

    std::pair<Key&, Info&> operator*() noexcept;
    std::pair<const Key&, const Info&> operator*() const noexcept;

    std::pair<Key&, Info&>* operator->() noexcept;
    std::pair<const Key&, const Info&>* operator->() const noexcept;

    bool operator==(iterator rhs) const noexcept;
    bool operator!=(iterator rhs) const noexcept;

    iterator operator++(int) const noexcept;
    iterator& operator++() const noexcept;
    iterator operator+(int rhs) const noexcept;
    iterator operator--(int) const noexcept;
    iterator& operator--() const noexcept;
    iterator operator-(int rhs) const noexcept;

    //element access
    Key& get_key() noexcept;
    const Key& get_key() const noexcept;
    Info& get_info() noexcept;
    const Info& get_info() const noexcept;

    ~iterator() = default;
};

#include "ring_iter.tpp"
