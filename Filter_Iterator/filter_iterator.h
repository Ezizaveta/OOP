#pragma once
#include <type_traits>
#include <iterator>
#include <stdexcept>
#include <optional>

template <class Predicate, class Iterator,
    typename = std::enable_if_t<std::is_convertible_v<
    typename std::iterator_traits<Iterator>::iterator_category, std::forward_iterator_tag>>>
class filter_iterator final
{
private:
    Predicate m_pred;
    std::optional<Iterator> m_iter;
    std::optional<Iterator> m_end;

    void move_iter()
    {
        while ((m_iter != m_end) && !(m_pred(**m_iter)))
        {
            (*m_iter)++;
        }
    };

public:
    using value_type = std::iterator_traits<Iterator>::value_type;
    using reference = std::iterator_traits<Iterator>::reference;
    using pointer = std::iterator_traits<Iterator>::pointer;
    using difference_type  = std::iterator_traits<Iterator>::difference_type;
    using iterator_category  = std::iterator_traits<Iterator>::iterator_category;
    
    filter_iterator(typename std::enable_if <std::is_default_constructible_v<Predicate>
        && std::is_default_constructible_v<Iterator>>::type* = 0) {};

    filter_iterator(Predicate predicate, Iterator iter, Iterator end = Iterator()) :
        m_pred(predicate), m_iter(iter), m_end(end) {
        move_iter();
    }

    filter_iterator(Iterator iter, Iterator end = Iterator(), typename std::enable_if<
        std::is_default_constructible_v <Predicate> && std::is_class_v <Predicate>>::type* = 0) :
        m_pred(), m_iter(iter), m_end(end) {
        move_iter();
    };

  
    reference operator*() 
    {
        if (m_iter == m_end)
        {
            throw std::out_of_range("Can't dereference end iterator");
        }
        return *(m_iter.value());
    };
    const value_type& operator*() const //здесь косяк, не получается разыменовать фильтр итератор для фильтр итератора
    {
        if (m_iter == m_end)
        {
            throw std::out_of_range("Can't dereference end iterator");
        }
        return *(m_iter.value());
    };

    filter_iterator& operator++()
    {
        if (m_iter == m_end)
        {
            throw std::out_of_range("Can't increment end iterator");
        }
        (*m_iter)++;
        move_iter();
        if (m_iter == m_end)
        {
            *this = filter_iterator();
        }
        return *this;
    };

    filter_iterator operator++(int)
    {
        auto tmp = *this;
        ++(*m_iter);
        return tmp;
    }

    bool operator==(const filter_iterator& other) const {
        if (*this == filter_iterator() || other == filter_iterator())
            return false;
        return *m_iter == *(other.m_iter);
    }

    bool operator!=(const filter_iterator& other) const
    {
        return this->m_iter != other.m_iter;
    }
};

template <class Predicate, class Iterator>
filter_iterator <Predicate, Iterator>
make_filter_iterator(Predicate pred, Iterator begin, Iterator end = Iterator())
{
    return filter_iterator<Predicate, Iterator>(pred, begin, end);
}

template <class Predicate, class Iterator,
    typename = std::enable_if< std::is_default_constructible_v <Predicate>&& std::is_class_v <Predicate>>>
filter_iterator <Predicate, Iterator>
make_filter_iterator(Iterator begin, Iterator end = Iterator())
{
    return filter_iterator <Predicate, Iterator>(begin, end);
}