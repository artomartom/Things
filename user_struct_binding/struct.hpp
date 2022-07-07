#ifndef BIND_STRUCT
#define BIND_STRUCT
#include <string>
#include <tuple>

#include <type_traits>
#if 0
class MyStruct
{
public:
    MyStruct &get_config()
    {
        return *this;
    };

    int get_x() { return x; };

private:
    int x{};
};

namespace std
{
    template <>
    struct std::tuple_size<MyStruct> : std::integral_constant<size_t, 1>
    {
    };
    template <>
    struct tuple_element<0, MyStruct>
    {
        using type = int;
    };

    template <>
    std::tuple_element_t<0, MyStruct> &get<0>(MyStruct &obj) { return obj.get_x(); };

}
#endif

class Person
{
public:
    std::string name;
    int age;
};

namespace std
{
    template <>
    struct tuple_size<::Person>
        : integral_constant<size_t, 2>
    {
    };
    template <>
    struct tuple_element<0, ::Person>
    {
        using type = std::string;
    };

    template <>
    struct tuple_element<1, ::Person>
    {
        using type = int;
    };

}

template <std::size_t Index>
std::tuple_element_t<Index, Person> &get(Person &person)
{

    if constexpr (Index == 0)
        return person.name;
    if constexpr (Index == 1)
        return person.age;
}

#endif // BIND_STRUCT
