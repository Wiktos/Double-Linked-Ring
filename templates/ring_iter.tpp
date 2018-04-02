template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator=(const typename Ring<Key, Info>::iterator& rhs) const noexcept{
    it = rhs.it;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator=(typename Ring<Key, Info>::iterator&& rhs) noexcept{
    it = std::move(rhs.it);
    rhs.it = nullptr;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Node& Ring<Key, Info>::iterator::operator*() noexcept{
    return *it;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::Node& Ring<Key, Info>::iterator::operator*() const noexcept{
    return *it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Node* Ring<Key, Info>::iterator::operator->() noexcept{
    return it;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::Node* Ring<Key, Info>::iterator::operator->() const noexcept{
    return it;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator==(typename Ring<Key, Info>::iterator rhs) const noexcept{
    return it == rhs.it;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator!=(typename Ring<Key, Info>::iterator rhs) const noexcept{
    return it != rhs.it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator++(int) const noexcept{
    iterator curr(it);
    it = it->next;
    return curr;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator++() const noexcept{
    it = it->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator+(int rhs) const noexcept{
    for(int i = 0; i < rhs; i++)
        it = it->next;

    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator--(int) const noexcept{
    iterator curr(it);
    it = it->prev;
    return curr;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator--() const noexcept{
    it = it->prev;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator-(int rhs) const noexcept{
    for(int i = 0; i < rhs; i++)
        it = it->prev;

    return *this;
}
