#pragma once

#include <iostream>
#include <vector>

namespace Good
{
    template <typename _KeyT, typename _ElemT>
    class Map
    {
    public:
        using KeyType = _KeyT;
        using ElemType = _ElemT;
        using VectorType = std::vector<std::pair<_KeyT, _ElemT>>;
        using SelfType = Map<_KeyT, _ElemT>;

    public:
        std::vector<std::pair<_KeyT, _ElemT>> m_data;

    public:
        Map() {}
        ~Map() {}

    public:
        _ElemT &operator[](size_t index)
        {
            return m_data.at(index);
        }

    public:
        size_t npos()
        {
            return m_data.size();
        }

        _ElemT &get_value(_KeyT key)
        {
            return m_data.at(find_key(key)).second;
        }

        bool contain_key(_KeyT key)
        {
            size_t index = find_key(key);
            return (index != npos());
        }

        size_t find_key(_KeyT key)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                if (m_data.at(i).first == key)
                {
                    return i;
                }
            }
            return npos();
        }

        size_t find_key(_KeyT key, bool (*comparer)(_KeyT, _KeyT))
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                if (comparer(m_data.at(i).first, key))
                {
                    return i;
                }
            }
            return npos();
        }

        Map &insert(std::pair<_KeyT, _ElemT> data)
        {
            m_data.push_back(data);
            return *this;
        }

        Map &insert(const _KeyT &key, const _ElemT &elem)
        {
            m_data.push_back(std::pair<_KeyT, _ElemT>(key, elem));
            return *this;
        }

        size_t size()
        {
            return m_data.size();
        }
    };
} // namespace Good
