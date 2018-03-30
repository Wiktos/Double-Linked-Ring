template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Ring<Key, Info>& ring){
    typename Ring<Key, Info>::Node *curr = ring.any;
    if(!curr)
        return os;

    do{
        os << curr->key << ' ' << curr->info << '\n';
        curr = curr->next;
    }
    while(curr != ring.any);

    return os;
}

template <typename Key, typename Info>
struct Ring<Key, Info>::Node
{
    Key key;
    Info info;
    Node *prev;
    Node *next;
};

template <typename Key, typename Info>
class Ring<Key, Info>::RingInvalidArgument final : public std::invalid_argument
{
public:
    using std::invalid_argument::invalid_argument;
};

template <typename Key, typename Info>
void Ring<Key, Info>::push(const Key& key, const Info& info){
    if(!any){
        any = new Node{key, info};
        any->next = any;
        any->prev = any;
        length++;
        return;
    }

    Node *new_elem = new Node{key, info, any->prev, any};
    any->prev->next = new_elem;
    any->prev = new_elem;
    length++;
}
