#pragma once
#include <memory>

class Node final
{
    using Data_t = int;
    using pNextNode_t = std::unique_ptr<Node>;

public:
    Node() = default;
    Node(Data_t &&data)
        : m_data{std::move(data)},
          m_left{nullptr},
          m_right{nullptr} {};

    Node(const Data_t &data)
        : m_data{data},
          m_left{nullptr},
          m_right{nullptr} {};

    static pNextNode_t NewNode(Data_t &&data) { return std::make_unique<Node>(std::forward<Data_t>(data)); };

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
        SetNodeData<&Node::HasLeft, &Node::m_left>(std::forward<Data_t>(data));
    };
    void Right(Data_t &&data)
    {
        SetNodeData<&Node::HasRight, &Node::m_right>(std::forward<Data_t>(data));
    };

    void Left(const Node &node){};
    void Right(const Node &node){};
    void Left(decltype(nullptr))
    {
        pNextNode_t tmp{nullptr};
        std::swap(m_left, tmp);
    };
    void Right(decltype(nullptr))
    {
        pNextNode_t tmp{nullptr};
        std::swap(m_right, tmp);
    };

    // Data: Set funcs
    void Data(Data_t &&data) { m_data = std::move(data); };
    // Data: Get funcs
    const Data_t &Data() const { return m_data; };
    Data_t &Data() { return m_data; };

private:
    template <bool (Node::*Presence_Pred)() const noexcept, pNextNode_t(Node::*which_node)>
    void SetNodeData(Data_t &&data)
    {
        if ((this->*Presence_Pred)())
        {
            (this->*which_node)->Data(std::forward<Data_t>(data));
        }
        else
            (this->*which_node) = NewNode(std::forward<Data_t>(data));
    };

    pNextNode_t m_left{nullptr};
    pNextNode_t m_right{nullptr};
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