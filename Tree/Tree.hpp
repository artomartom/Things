#pragma once
#include <memory>

using Data_t = int;

class Node final
{
    using NextNode = std::unique_ptr<Node>;

public:
    Node() = default;
    Node(Data_t &data)
        : m_data{data},
          m_left{nullptr},
          m_right{nullptr} {};

    static NextNode NewNode(Data_t &&data) { return std::make_unique<Node>(std::forward<Data_t>(data)); };

    // state: Get  funcs
    bool HasLeft() const noexcept { return m_left.get() != nullptr; };
    bool HasRight() const noexcept { return m_right.get() != nullptr; };

    // Get funcs
    const Node &Left() const { return *m_left.get(); };
    Node &Left() { return *m_left.get(); };
    const Node &Right() const { return *m_right.get(); };
    Node &Right() { return *m_right.get(); };

    // Set funcs
    void Left(Data_t &&data)
    {
        m_left = NewNode(std::forward<Data_t>(data));
    };
    void Right(Data_t &&data)
    {
        m_right = NewNode(std::forward<Data_t>(data));
    };

    // Data: Set funcs
    void Data(Data_t &&data) { m_data = std::move(data); };
    // Data: Get funcs
    const Data_t &Data() const { return m_data; };
    Data_t &Data() { return m_data; };

private:
    NextNode m_left{nullptr};
    NextNode m_right{nullptr};
    Data_t m_data{};
};

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << node.Data() << '\n';
    if (node.HasLeft())
    {
        os << node.Left();
    }
    if (node.HasRight())
    {
        os << node.Right();
    }
    return os;
}