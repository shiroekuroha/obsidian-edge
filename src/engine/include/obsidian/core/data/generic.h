#ifndef OE_GENERIC_H
#define OE_GENERIC_H

namespace ObsidianEdge
{
using String = std::string;

template <typename Tp, unsigned int Nm> using Array = std::array<Tp, Nm>;
template <typename Tp> using Vector = std::vector<Tp>;
template <typename Tp> using Deque = std::deque<Tp>;
template <typename Tp> using Queue = std::queue<Tp>;

template <typename First, typename Second> using Pair = std::pair<First, Second>;

template <typename T> using SharedPointer = std::shared_ptr<T>;
template <typename T> using UniquePointer = std::unique_ptr<T>;
}

#endif
