#ifndef BROKERAPP_UTILS_LIST_HPP
#define BROKERAPP_UTILS_LIST_HPP

#include <iostream>
#include <iterator>

template<class T>
struct Node {
    T data;
    Node<T> * next;
    Node<T> * prev;
};

template<class T>
class List {
private:
    class List_iterator;
    class List_reverse_iterator;
public:
    // Constructors:
    List();
    List(const List& other);
    List(std::initializer_list<T> ilist);
    // Destructors:
    ~List();

    // Functions: selectors (get)
    bool empty() const noexcept;
    T& front() const noexcept;
    T& back() const noexcept;
    const unsigned long long& size() const noexcept;

    List_iterator begin() const noexcept;
    List_iterator end() const noexcept;
    List_reverse_iterator rbegin() const noexcept;
    List_reverse_iterator rend() const noexcept;

    // Methods:
    void push_front(const T& x);
    void push_back(const T& x);
    const T pop_front();
    const T pop_back();
    void insert_after(List_iterator it, const T& x);
    List_iterator find(const T& x) const;
    void erase(List_iterator it);
    void clear();

    template<typename... ARGS>
    void emplace_front(ARGS&&... args);
    template<typename... ARGS>
    void emplace_back(ARGS&&... args);

    // Operators overloads:
    List& operator = (const List& other);
    List& operator = (std::initializer_list<T> ilist);
    T& operator [] (const int& index);
    const T& operator [] (const int& index) const;

    template<class U>
    friend std::ostream& operator << (std::ostream& os, const List<U>& li);

private:
    Node<T> * head;
    Node<T> * tail;
    unsigned long long sz;

    // Iterators:
    class List_iterator {
    private:
        friend class List;
    public:
        // Constructors:
        List_iterator(Node<T> * p = nullptr);

        T& operator * () const noexcept;
        Node<T> * operator -> () const noexcept;
        operator bool () const;

        List_iterator& operator ++ ();
        List_iterator operator ++ (int);
        List_iterator& operator -- ();
        List_iterator operator -- (int);

        bool operator == (const List_iterator& other) const noexcept;
        bool operator != (const List_iterator& other) const noexcept;
    
    protected:
        Node<T>* ptr;
    };

    class List_reverse_iterator : public List_iterator {
    public:
        using List_iterator::List_iterator;

        List_reverse_iterator& operator ++ ();
        List_reverse_iterator operator ++ (int);
        List_reverse_iterator& operator -- ();
        List_reverse_iterator operator -- (int);
    };
};

#include "list.tpp"

#endif // BROKERAPP_UTILS_LIST_HPP