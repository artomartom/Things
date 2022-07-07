
#include <iostream>

namespace ranges
{

    struct range
    {

        // template <typename T, typename U>
        // friend T reversed(U);

        using index_t = int;

    public:
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

        friend inline range in_range(index_t begin, index_t end);

        iterator begin() const noexcept { return iterator{m_begin}; };
        iterator end() const noexcept { return iterator{m_end}; };

    protected:
        explicit range(index_t begin, index_t end)
            : m_begin(begin), m_end(end){};
        index_t m_begin;
        index_t m_end;
    };

    struct step_range : protected range
    {
        template <typename T, typename U>
        friend T reversed(U);

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

        friend inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step);

        step_range::iterator begin() const noexcept { return step_range::iterator{range::m_begin, m_step}; };
        step_range::iterator end() const noexcept { return step_range::iterator{range::m_end, m_step}; };

    protected:
        explicit step_range(index_t begin, index_t end, index_t step)
            : range{begin, end},
              m_step{step} {};
        index_t m_step{};
    };

    struct reversed_range : public range
    {
        template <typename T, typename U>
        friend T reversed(U);

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

        friend inline reversed_range in_reversed_range(reversed_range::index_t begin, reversed_range::index_t end);

        reversed_range::iterator begin() const noexcept { return reversed_range::iterator{range::m_begin}; };
        reversed_range::iterator end() const noexcept { return reversed_range::iterator{range::m_end}; };

    protected:
        explicit reversed_range(index_t begin, index_t end)
            : range{begin - 1, end} {};
    };

    // reverse
     template <>
     reversed_range reversed(const range &r)
     {
         return reversed_range{r};
     };
    // template <>
    // reversed_range reversed(const step_range &r)
    // {
    //     return reversed_range{r};
    // };
    // template <>
    // range reversed(const reversed_range &r)
    // {
    //     return reversed_range{r};
    // };

    //
    inline range in_range(range::index_t begin, range::index_t end)
    {
        return range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step)
    {
        return step_range{begin, end, step};
    };
    inline reversed_range in_reversed_range(reversed_range::index_t begin, reversed_range::index_t end)
    {
        return reversed_range{begin, end};
    };

};

using namespace ranges;
int main()
{

    std::cout << "      in_range(0, 10)\n";
    for (auto e : in_range(0, 10))
        std::cout << "Hello World " << e << "th time\n";

    //  std::cout << " reversed(in_range(0, 10))\n";
    //  for (auto e : reversed(in_range(0, 10)))
    //      std::cout << "Hello World " << e << "th time\n";

     std::cout << "     in_range(0, 10, 1)\n";
     for (auto e : in_range(0, 10, 1))
         std::cout << "Hello World " << e << "th time\n";

    // std::cout << "reversed(in_range(0, 10, 1))\n";
    // for (auto e : reversed(in_range(0, 10, 1)))
    //     std::cout << "Hello World " << e << "th time\n";

      std::cout << "    in_reversed_range(10, 0)\n";
      for (auto e : in_reversed_range(10, 0))
          std::cout << "Hello World " << e << "th time\n";

    // std::cout << "in_range(0, 10)\n";
    // for (auto e : in_range(0, 10))
    //     std::cout << "Hello World " << e << "th time\n";

    // std::cout << "reversed(in_reversed_range(10, 0))\n";
    // for (auto e : reversed(in_reversed_range(10, 0)))
    //     std::cout << "Hello World " << e << "th time\n";

    return 0;
}
