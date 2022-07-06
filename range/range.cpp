
#include <iostream>

struct range
{
    using integer_t = int;
    struct iterator
    {
    public:
        explicit iterator(integer_t index)
            : m_index(index){};
        iterator() = delete;
        virtual ~iterator() = default;

        bool operator!=(const iterator &other) const noexcept { return m_index < other.m_index; }; // WARNING: this very bad and i'm, for sure, going to hell (1)
        integer_t &operator++() noexcept { return ++m_index; };
        integer_t operator*() noexcept { return m_index; };

    protected:
        integer_t m_index{};

    public:
        using value_type = integer_t;
        using difference_type = decltype(value_type{} - value_type{});
        using iterator_category = std::input_iterator_tag;
        using pointer = value_type *;
        using reference = value_type &;
    };

public:
    explicit range(integer_t begin, integer_t end)
        : m_begin(begin), m_end(end){};
    iterator begin() const noexcept { return iterator{m_begin}; };
    iterator end() const noexcept { return iterator{m_end}; };

protected:
    integer_t m_begin;
    integer_t m_end;
};

struct step_range : protected range
{
    using integer_t = range::integer_t;

public:
    struct iterator : public range::iterator
    {
    public:
        explicit iterator(integer_t index, integer_t step)
            : range::iterator{index},
              m_step{step} {};
        integer_t &operator++() noexcept { return iterator::m_index += m_step; };

    protected:
        integer_t m_step{};
    };

    explicit step_range(integer_t begin, integer_t end, integer_t step)
        : range{begin, end},
          m_step{step} {};

    step_range::iterator begin() const noexcept { return step_range::iterator{range::m_begin, m_step}; };
    step_range::iterator end() const noexcept { return step_range::iterator{range::m_end, m_step}; };

protected:
    integer_t m_step{};
};

struct reversed_range : protected range
{
    using integer_t = range::integer_t;

public:
    struct iterator : public range::iterator
    {
    public:
        explicit iterator(integer_t index)
            : range::iterator{index} {};
        bool operator!=(const iterator &other) const noexcept { return m_index >= other.m_index; };
        integer_t &operator++() noexcept { return --iterator::m_index; };
    };

    explicit reversed_range(integer_t begin, integer_t end)
        : range{begin - 1, end} {};

    reversed_range::iterator begin() const noexcept { return reversed_range::iterator{range::m_begin}; };
    reversed_range::iterator end() const noexcept { return reversed_range::iterator{range::m_end}; };
};

//
range in_range(range::integer_t begin, range::integer_t end)
{
    return range{begin, end};
};
step_range in_range(step_range::integer_t begin, step_range::integer_t end, step_range::integer_t step)
{
    return step_range{begin, end, step};
};
reversed_range in_reversed_range(reversed_range::integer_t begin, reversed_range::integer_t end)
{
    return reversed_range{begin, end};
};

template <typename range, typename... integer_t>
range make_range(integer_t... args)  
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
