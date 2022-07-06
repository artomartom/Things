
#include <iostream>

struct range
{
    using index_t = int;
    struct iterator
    {
    public:
        explicit iterator(index_t index)
            : m_index(index){};
        iterator() = delete;
        virtual ~iterator() = default;

        bool operator!=(const iterator &other) const noexcept { return m_index < other.m_index; }; // WARNING: this very bad and i'm, for sure, going to hell (1)
        index_t &operator++() noexcept { return ++m_index; };
        index_t operator*() noexcept { return m_index; };

    protected:
        index_t m_index{};

    public:
        using value_type = index_t;
        using difference_type = decltype(value_type{} - value_type{});
        using iterator_category = std::input_iterator_tag;
        using pointer = value_type *;
        using reference = value_type &;
    };

public:
    explicit range(index_t begin, index_t end)
        : m_begin(begin), m_end(end){};
    iterator begin() const noexcept { return iterator{m_begin}; };
    iterator end() const noexcept { return iterator{m_end}; };

protected:
    index_t m_begin;
    index_t m_end;
};

struct step_range : protected range
{
    using index_t = range::index_t;

public:
    struct iterator : public range::iterator
    {
    public:
        explicit iterator(index_t index, index_t step)
            : range::iterator{index},
              m_step{step} {};
        index_t &operator++() noexcept { return iterator::m_index += m_step; };

    protected:
        index_t m_step{};
    };

    explicit step_range(index_t begin, index_t end, index_t step)
        : range{begin, end},
          m_step{step} {};

    step_range::iterator begin() const noexcept { return step_range::iterator{range::m_begin, m_step}; };
    step_range::iterator end() const noexcept { return step_range::iterator{range::m_end, m_step}; };

protected:
    index_t m_step{};
};

struct reversed_range : protected range
{
    using index_t = range::index_t;

public:
    struct iterator : public range::iterator
    {
    public:
        explicit iterator(index_t index)
            : range::iterator{index} {};
        bool operator!=(const iterator &other) const noexcept { return m_index >= other.m_index; };
        index_t &operator++() noexcept { return --iterator::m_index; };
    };

    explicit reversed_range(index_t begin, index_t end)
        : range{begin - 1, end} {};

    reversed_range::iterator begin() const noexcept { return reversed_range::iterator{range::m_begin}; };
    reversed_range::iterator end() const noexcept { return reversed_range::iterator{range::m_end}; };
};
template <typename range, typename... index_t>
range make_range(index_t... args)  
{
    return range{args...};
};
int main()
{

    std::cout << "\n";
    for (auto e : make_range<range>(0, 10))
        std::cout << "Hello World " << e << "th time\n";

    std::cout << "\n";
    for (auto e : make_range<step_range>(0, 10, 1))
        std::cout << "Hello World " << e << "th time\n";

    std::cout << "\n";
    for (auto e : make_range<reversed_range>(10, 0))
        std::cout << "Hello World " << e << "th time\n";

    return 0;
}
