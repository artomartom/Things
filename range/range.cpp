
#include <iostream>
#include <assert.h>

namespace ranges
{
    struct stable
    {
    };

    template <typename T>
    struct range_iterator_trait
    {
        using value_type = T;
        using difference_type = decltype(value_type{} - value_type{});
        using iterator_category = std::input_iterator_tag;
        using pointer = value_type *;
        using reference = value_type &;
    };

    struct range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator
        {
        public:
            explicit iterator(index_t index)
                : m_index(index){};
            iterator() = delete;
            virtual ~iterator() = default;

            bool operator!=(const iterator &other) const noexcept { return m_index != other.m_index; };
            index_t &operator++() noexcept { return ++m_index; };
            index_t operator*() noexcept { return m_index; };

        protected:
            index_t m_index{};

        public:
        };

        // factory
        friend inline range in_range(index_t begin, index_t end);
        friend inline range in_range(index_t begin, index_t end, stable);

        iterator begin() const noexcept { return iterator{m_begin}; };
        iterator end() const noexcept { return iterator{m_end}; };

    protected:
        explicit range(index_t begin, index_t end)
            : m_begin(begin), m_end(end){};
        index_t m_begin;
        index_t m_end;
    };

    struct reversed_range : public range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator : public range::iterator
        {
        public:
            explicit iterator(index_t index)
                : range::iterator{index} {};
            bool operator!=(const iterator &other) const noexcept { return m_index != other.m_index; };
            index_t &operator++() noexcept { return --iterator::m_index; };
        };
        // factory
        friend inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end);
        friend inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end, stable);

        reversed_range::iterator begin() const noexcept { return reversed_range::iterator{range::m_begin}; };
        reversed_range::iterator end() const noexcept { return reversed_range::iterator{range::m_end}; };

    protected:
        explicit reversed_range(index_t begin, index_t end)
            : range{begin - 1, end} {};
    };
    struct step_range : protected range
    {

        using index_t = range_iterator_trait<int>::value_type;

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
        // factory
        friend inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step);
        friend inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step, stable);

        step_range::iterator begin() const noexcept { return step_range::iterator{range::m_begin, m_step}; };
        step_range::iterator end() const noexcept { return step_range::iterator{range::m_end, m_step}; };

    protected:
        explicit step_range(index_t begin, index_t end, index_t step)
            : range{begin, end},
              m_step{step} {};
        index_t m_step{};
    };

    struct reversed_step_range : protected step_range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator : public step_range::iterator
        {
        public:
            explicit iterator(index_t index, index_t step)
                : step_range::iterator{index, step} {};
            bool operator!=(const iterator &other) const noexcept { return m_index >= other.m_index; };
            index_t &operator++() noexcept { return iterator::m_index += m_step; };
        };
        // factory
        friend inline reversed_step_range reversed_in_range(index_t begin, index_t end, index_t step);
        friend inline reversed_step_range reversed_in_range(index_t begin, index_t end, index_t step, stable);

        reversed_step_range::iterator begin() const noexcept { return reversed_step_range::iterator{range::m_begin, m_step}; };
        reversed_step_range::iterator end() const noexcept { return reversed_step_range::iterator{range::m_end, m_step}; };

    protected:
        explicit reversed_step_range(index_t begin, index_t end, index_t step)
            : step_range{begin - 1, end, step} {};
    };

    // factory
    inline range in_range(range::index_t begin, range::index_t end)
    {
        return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end)
    {
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step)
    {
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::index_t begin, reversed_step_range::index_t end, reversed_step_range::index_t step)
    {
        return reversed_step_range{begin, end, step};
    };

// stable factory
#ifdef STABLE
    inline range in_range(range::index_t begin, range::index_t end, stable)
    {
        if (begin > end)
            return range{end, begin};
        else
            return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end, stable)
    {
        //     if (begin > end)else
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step, stable)
    {
        // if(step<0 )       step=-step;

        //     if (begin > end)else
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::index_t begin, reversed_step_range::index_t end, reversed_step_range::index_t step, stable)
    {
        // if(step<0 )       step=-step;
        //      if (begin > end)else
        return reversed_step_range{begin, end, step};
    };
#endif // STABLE

};

using namespace ranges;
int main()
{

    for (int i{}; auto e : in_range(0, 10))
    {
        assert(i != 10);
        assert(e == i);
        i++;
    }

    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        assert(e == i);
        assert(i != 10);
        i--;
    }

    for (int i{}; auto e : in_range(0, 10, 1))
    {
        assert(i != 10);
        assert(e == i);
        i++;
    }

    for (int i{9}; auto e : reversed_in_range( 0,10, 1))
    {
        assert(e == i);
        assert(i != 10);
        i--;
    }

    std::cout << "lol\n";
    // stable

    // std::cout << "      in_range(0, 10,stable{})\n";
    // for (auto e : in_range(0, 10,stable{}))
    //     std::cout << "Hello World " << e << "th time\n";

    // std::cout << "    reversed_in_range(10, 0,stable{})\n";
    // for (auto e : reversed_in_range(10, 0,stable{}))
    //     std::cout << "Hello World " << e << "th time\n";

    // std::cout << "     in_range(0, 10, 1,stable{})\n";
    // for (auto e : in_range(0, 10, 1))
    //     std::cout << "Hello World " << e << "th time\n";

    // std::cout << "    reversed_in_range(10, 0,stable{})\n";
    // for (auto e : reversed_in_range(10, 0, 1,stable{}))
    //     std::cout << "Hello World " << e << "th time\n";

    return 0;
}
