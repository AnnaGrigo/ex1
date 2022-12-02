
#ifndef RATUV1_PAIR_H
#define RATUV1_PAIR_H

template <class Key, class Value>
class Pair
{
public:
    Key key;
    Value value;
    Pair() =default;
    Pair(const Pair<Key, Value> &other)
    {
        this->key = other.key;
        this->value = other.value;
    }


    friend bool operator<(Pair<Key, Value> pair1, Pair<Key, Value> pair2)
    {
        return pair1.key < pair2.key;
    }
};
#endif //RATUV1_PAIR_H
