#ifndef BROKERAPP_UTILS_LIST_HPP
#define BROKERAPP_UTILS_LIST_HPP

#include <iostream>
#include <iterator>

// FIXME: rewrite list to use shared_ptr instead of raw pointers  

template<class T>
struct node_t {
    T data;
    node_t<T> * next;
    node_t<T> * prev;
};

template<class T>
class list {
private:
    class List_iterator;
    class List_reverse_iterator;
public:
    // Constructors:
    list();
    list(const list& other);
    list(std::initializer_list<T> ilist);
    // Destructors:
    ~list();

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
    list& operator = (const list& other);
    list& operator = (std::initializer_list<T> ilist);
    T& operator [] (const int& index);
    const T& operator [] (const int& index) const;

    template<class U>
    friend std::ostream& operator << (std::ostream& os, const list<U>& li);

private:
    node_t<T> * head;
    node_t<T> * tail;
    unsigned long long sz;

    // Iterators:
    class List_iterator {
    private:
        friend class list;
    public:
        // Constructors:
        List_iterator(node_t<T> * p = nullptr);

        T& operator * () const noexcept;
        node_t<T> * operator -> () const noexcept;
        operator bool () const;

        List_iterator& operator ++ ();
        List_iterator operator ++ (int);
        List_iterator& operator -- ();
        List_iterator operator -- (int);

        bool operator == (const List_iterator& other) const noexcept;
        bool operator != (const List_iterator& other) const noexcept;
    
    protected:
        node_t<T>* ptr;
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