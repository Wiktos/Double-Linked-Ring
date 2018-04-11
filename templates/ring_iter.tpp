template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator=(const typename Ring<Key, Info>::iterator& rhs) noexcept{
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
std::pair<Key&, Info&> Ring<Key, Info>::iterator::operator*(){
    return std::make_pair(std::ref(it->key), std::ref(it->info));
}

template <typename Key, typename Info>
std::pair<const Key&, const Info&> Ring<Key, Info>::iterator::operator*() const{
    return std::make_pair(std::ref(it->key), std::ref(it->info));
}

template <typename Key, typename Info>
std::pair<Key&, Info&>* Ring<Key, Info>::iterator::operator->(){
    node_view = std::unique_ptr<std::pair<Key&, Info&>>(new std::pair<Key&, Info&>(std::ref(it->key), std::ref(it->info))).get();
    return node_view;
}

template <typename Key, typename Info>
const std::pair<Key&, Info&>* Ring<Key, Info>::iterator::operator->() const{
    node_view = std::unique_ptr<std::pair<Key&, Info&>>(new std::pair<Key&, Info&>(std::ref(it->key), std::ref(it->info))).get();
    return node_view;
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
    iterator curr(it);
    for(int i = 0; i < rhs; i++)
        curr.it = curr.it->next;

    return curr;
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
    iterator curr(it);
    for(int i = 0; i < rhs; i++)
        curr.it = curr.it->prev;

    return curr;
}

template <typename Key, typename Info>
Key& Ring<Key, Info>::iterator::get_key() noexcept{
    return it->key;
}

template <typename Key, typename Info>
const Key& Ring<Key, Info>::iterator::get_key() const noexcept{
    return it->key;
}

template <typename Key, typename Info>
Info& Ring<Key, Info>::iterator::get_info() noexcept{
    return it->info;
}

template <typename Key, typename Info>
const Info& Ring<Key, Info>::iterator::get_info() const noexcept{
    return it->info;
}
