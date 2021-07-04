#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <array>
#include <limits>
//#include <compare>
#include <random>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>
#include <string>

#include "check.h"
#include "rbtree.h"
#include "avltree.h"

template <template <typename> class BST>
void tree_test()
{
    const size_t limit = 10000;
    std::vector<size_t> input;
    input.reserve(limit);
    for (size_t i = 0; i < limit; ++i) {
        input.push_back(i);
    }
    {
        BST<size_t> tree;
        for (auto n : input) {
            tree.insert(n);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", n);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
        }
        for (auto n : input) {
            tree.erase(n);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", n);
        }
    }
    {
        BST<size_t> tree;
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            tree.insert(*i);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", *i);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
        }
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            tree.erase(*i);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", *i);
        }
    }
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(input), std::end(input), g);
        BST<size_t> tree;
        for (auto n : input) {
            tree.insert(n);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", n);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
            BST<size_t> third(std::move(other));
            examine(tree != other, "move constructor is failed\n");
            examine(tree == third, "move constructor is failed\n");
            for (auto n : input) {
                third.erase(n);
                examine(third.valid(), "after removing %zu, the tree is illegal\n", n);
            }
        }
        for (auto n : input) {
            tree.erase(n);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", n);
        }
    }
}

template <typename T>
struct Operation
{
    T key;
    enum Op { INSERTING, DELETING, FINDING } opertion;

    Operation(T k = 0, Op i = INSERTING) : key(k), opertion(i) {}
};

template <typename N>
N randnum(N start, N end)
{
    assert(start <= end);
    N diff = static_cast<N>(end - start + 1);
    N r = static_cast<N>(rand());
    r %= diff;
    return r + start;
}

template <typename T>
std::vector<Operation<T>> get_hybrid_operations(std::vector<T> const& input)
{
    using difference_type = typename std::vector<T>::iterator::difference_type;
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<Operation<T>> retval;
    size_t upper_limit = input.size();
    retval.reserve(upper_limit);
    std::vector<T> deleting;
    size_t start = 0;
    while (start < upper_limit) {
        auto end = std::min(start + 20, upper_limit);
        auto v = randnum(start, end);
        if (v == start) {
            ++v;
        }
        for (auto i = start, ie = std::min(v, upper_limit); i < ie; ++i) {
            retval.emplace_back(input[i], Operation<T>::INSERTING);
        }
        deleting.insert(
            deleting.end(),
            input.begin() + static_cast<difference_type>(start),
            input.begin() + static_cast<difference_type>(v)
        );
        start = v;

        end = std::min(start + 60, upper_limit);
        v = randnum(start, end);
        if (v == start) {
            ++v;
        }
        for (auto i = start, ie = std::min(v, upper_limit); i < ie; ++i) {
            retval.emplace_back(input[i], Operation<T>::FINDING);
        }

        auto dl = deleting.size();
        if (dl > 0) {
            v = randnum<decltype(dl)>(0, dl);
            if (v == 0) {
                v = 1;
            }
            for (decltype(v) i = 0; i < v; ++i) {
                retval.emplace_back(deleting[i], Operation<T>::DELETING);
            }
            deleting = std::vector<T>(deleting.begin() + static_cast<difference_type>(v), deleting.end());
        }
    }
    for (auto v : deleting) {
        retval.emplace_back(v, Operation<T>::DELETING);
    }
    return retval;
}

template <typename T>
inline double run(const std::vector<Operation<T>>& operations)
{
    auto begin = std::chrono::system_clock::now();
    std::pmr::set<T> tree;
    for (auto const& o : operations) {
        switch (o.opertion) {
        case Operation<T>::INSERTING:
            tree.insert(o.key);
            break;
        case Operation<T>::DELETING:
            tree.erase(o.key);
            break;
        case Operation<T>::FINDING:
            {
                [[maybe_unused]] auto r = tree.find(o.key);
                break;
            }
        }
    }
    auto end = std::chrono::system_clock::now();
    return std::chrono::duration<double>(end - begin).count();
}

template <template <typename> class BST, typename T>
inline double run(const std::vector<Operation<T>>& operations)
{
    auto begin = std::chrono::system_clock::now();
    BST<T> tree;
    for (auto const& o : operations) {
        switch (o.opertion) {
        case Operation<T>::INSERTING:
            tree.insert(o.key);
            break;
        case Operation<T>::DELETING:
            tree.erase(o.key);
            break;
        case Operation<T>::FINDING:
            tree.contains(o.key);
            break;
        }
    }
    auto end = std::chrono::system_clock::now();
    return std::chrono::duration<double>(end - begin).count();
}

template <typename T>
void performance_test(const char* name, bool verifying, std::vector<T>& input)
{
    int times = 200;
    if (verifying) {
        times = 3;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    double set_duration = 0, rdtree_duration = 0, avltree_duration = 0;
    for (int i = 0; i < times; ++i) {
        auto operations = get_hybrid_operations<T>(input);
        set_duration += run<T>(operations);
        rdtree_duration += run<RedBlackTree, T>(operations);
        avltree_duration += run<AVLTree, T>(operations);
        std::shuffle(std::begin(input), std::end(input), g);
    }
    printf(
        "insert/erase/find %7zu %7ss (sizeof: %3zu bytes) %d times\tstd set: %fs\tred-black tree: %fs (%4.2f%%)\tavl tree: %fs (%4.2f%%)\n",
        input.size(), name, sizeof(T), times,
        set_duration,
        rdtree_duration, (rdtree_duration/set_duration) * 100,
        avltree_duration, (avltree_duration/set_duration) * 100
    );
}

template <typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class Student
{
public:
    enum Gender : int {MALE, FEMALE};

    Student(
        size_t _id,
        std::pmr::string&& _name,
        size_t _age,
        Gender _gender,
        std::pmr::string&& _address
    ) :
        id(_id),
        name(std::move(_name), Allocator()),
        age(_age),
        gender(_gender),
        address(std::move(_address), Allocator())
    {
    }

#if 0
    auto operator<=>(const Student& rhs) const
    {
        return id <=> rhs.id;
    }
#else
    bool operator==(const Student& rhs) const
    {
        return id == rhs.id;
    }
    bool operator<(const Student& rhs) const
    {
        return id < rhs.id;
    }
#endif
private:
    size_t id;
    std::pmr::string name;
    size_t age;
    Gender gender;
    std::pmr::string address;
};

void performance_test_for_students(size_t input_length, bool verifying)
{
    const size_t longest_length = 128;
    //std::array<char, longest_length + 1> buf;
    auto generate_random_string = [/*&buf*/](size_t shortest_length, size_t longest_length) {
    #if 0
        size_t n = randnum(shortest_length, longest_length);
        for (size_t i = 0; i < n; ++i) {
            buf[i] = randnum('0', 'z');
        }
        buf[n] = '\0';
        return std::pmr::string(&buf[0]);
    #else
        const char * template_string = "This is a series of interactive exercises for learning Microsoft's Reactive Extensions (Rx) Library for Javascript. So why is the title \"Functional Programming in Javascript\"?";
        size_t n = randnum(shortest_length, longest_length);
        return std::pmr::string(template_string, template_string + n);
    #endif
    };

    std::vector<Student<>> input;
    input.reserve(input_length);
    for (size_t i = 0; i < input_length; ++i) {
        input.emplace_back(
            i,
            generate_random_string(4, longest_length/2),
            (static_cast<size_t>(rand()) % 20) + 6,
            (rand() & 1) == 0 ? Student<>::MALE : Student<>::FEMALE,
            generate_random_string(10, longest_length)
        );
    }
    performance_test<Student<>>("student", verifying, input);
}

inline void print_separator()
{
    std::vector<char> buf(166, '_');
    buf.push_back('\0');
    puts(&buf[0]);
}

void performance_test_for_integers(size_t input_length, bool verifying)
{
    std::vector<int64_t> input;
    input.reserve(input_length);
    for (int64_t i = 0, ie = static_cast<int64_t>(input_length); i < ie; ++i) {
        input.emplace_back(i);
    }
    performance_test<int64_t>("integer", verifying, input);
}

class Block
{
public:
    std::array<uint8_t, 256> data;

    bool operator==(const Block& rhs) const
    {
        return memcmp(&data[0], &rhs.data[0], data.size()) == 0;
    }
    bool operator<(const Block& rhs) const
    {
        return memcmp(&data[0], &rhs.data[0], data.size()) < 0;
    }
};

void performance_test_for_blocks(size_t input_length, bool verifying)
{
    auto generate_block = []() {
        Block retval;
        int * pi = reinterpret_cast<int*>(&retval.data[0]);
        for (size_t i = 0, ie = 256 / sizeof(int); i < ie; ++i, ++pi) {
            *pi = rand();
        }
        return retval;
    };

    std::vector<Block> input;
    input.reserve(input_length);
    for (size_t i = 0; i < input_length; ++i) {
        input.emplace_back(generate_block());
    }
    performance_test<Block>("block", verifying, input);
}

template <typename F>
void performance_test(const std::vector<size_t>& input_lengths, F f, bool verifying)
{
    size_t n = input_lengths.size();
    if (verifying) {
        if (n > 4) {
            n = 4;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        f(input_lengths[i], verifying);
    }
    print_separator();
}

int main(int argc, char* argv[])
{
    bool verifying = false;
    if (argc > 1 && strcmp(argv[1], "verify") == 0) {
        verifying = true;
    }
    try {
        tree_test<RedBlackTree>();
        tree_test<AVLTree>();
        std::vector<size_t> input_lengths = {13, 149, 1597, 15679, 178979, 1956789, 3934567};
        performance_test(input_lengths, performance_test_for_integers, verifying);
        performance_test(input_lengths, performance_test_for_blocks, verifying);
        performance_test(input_lengths, performance_test_for_students, verifying);
        return 0;
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
}
