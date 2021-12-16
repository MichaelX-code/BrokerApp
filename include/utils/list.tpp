// Constructors:

template<class T>
List<T>::List()
{
    this->head = this->tail = nullptr;
    this->sz = 0;
}

template<class T>
List<T>::List(const List<T>& other) :
List()
{
    for (auto x : other)
        this->push_back(x);

    this->sz = other.size();
}

template<class T>
List<T>::List(std::initializer_list<T> ilist) :
List()
{
    for (auto x : ilist)
        this->push_back(x);

    this->sz = ilist.size();
}

// Destructors:

template<class T>
List<T>::~List()
{
    while(this->head)
        this->pop_front();
}

// Methods:

template<class T>
void
List<T>::push_front(const T& x)
{
    Node<T>* new_element = new Node<T>;
    new_element->data = x;
    new_element->next = nullptr;

    if (this->empty())
    {
        new_element->prev = nullptr;
        this->head = new_element;
    }
    else
    {
        this->head->prev = new_element;
        new_element->next = this->head;
    }
    
    this->head = new_element;
    ++sz;
}

template<class T>
void
List<T>::push_back(const T& x)
{
    Node<T>* new_element = new Node<T>;
    new_element->data = x;
    new_element->next = nullptr;

    if (this->empty())
    {
        new_element->prev = nullptr;
        this->head = new_element;
    }
    else
    {
        this->tail->next = new_element;
        new_element->prev = this->tail;
    }

    this->tail = new_element;
    ++sz;
}

template<typename T>
template<typename... ARGS>
void
List<T>::emplace_front(ARGS&&... args)
{
    Node<T>* new_element = new Node<T>;
    new_element->data = std::move(T(std::forward<ARGS>(args)...));
    new_element->next = nullptr;

    if (this->empty())
    {
        new_element->prev = nullptr;
        this->head = new_element;
    }
    else
    {
        this->head->prev = new_element;
        new_element->next = this->head;
    }

    this->head = new_element;
    ++sz;
}

template<typename T>
template<typename... ARGS>
void
List<T>::emplace_back(ARGS&&... args)
{
    Node<T>* new_element = new Node<T>;
    new_element->data = std::move(T(std::forward<ARGS>(args)...));
    new_element->next = nullptr;

    if (this->empty())
    {
        new_element->prev = nullptr;
        this->head = new_element;
    }
    else
    {
        this->tail->next = new_element;
        new_element->prev = this->tail;
    }

    this->tail = new_element;
    ++sz;
}

template<class T>
const T
List<T>::pop_front()
{
    T data;
    if (!this->head)
    {
        std::cerr << "ERROR: List is already empty!";
        exit(1);
    }

    if (this->head == this->tail)
    {
        data = this->head->data;
        this->head = this->tail = nullptr;
    }
    else
    {
        data = this->head->data;
        this->head = this->head->next;
        this->head->prev = nullptr;
    }
    
    --sz;
    return data;
}

template<class T>
const T
List<T>::pop_back()
{
    T data;
    if (!this->head)
    {
        std::cerr << "ERROR: List is already empty!";
        exit(1);
    }
    if (this->head == this->tail)
    {
        data = this->head->data;
        this->head = this->tail = nullptr;
    }
    else
    {
        data = this->head->data;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
    }
    
    --sz;
    return data;
}

template<class T>
void
List<T>::insert_after(List_iterator it, const T& x)
{
    Node<T>* new_element = new Node<T>;
    new_element->data = x;
    if (it == this->tail)
    {
        new_element->next = nullptr;
        new_element->prev = it.ptr;
        it->next = new_element;
        this->tail = new_element;
    }
    else
    {
        it->next->prev = new_element;
        new_element->next = it->next;
        new_element->prev = it.ptr;
        it->next = new_element;
    }
    ++sz;
}

template<class T>
typename List<T>::List_iterator
List<T>::find(const T& x)
const
{
    for (auto it = this->begin(); it; ++it)
        if (it->data == x)
            return it;
    return nullptr;
}

template<class T>
void
List<T>::erase(List_iterator it)
{
    if (it == this->head && it == this->tail)
    {
        this->head = this->tail = nullptr;
    }
    else if (it == this->head)
    {
        this->head = this->head->next;
        this->head->prev = nullptr;
    }
    else if (it == this->tail)
    {
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
    }
    else
    {
        it->next->prev = it->prev;
        it->prev->next = it->next;
    }

    delete it.ptr;
    --sz;
}

template<class T>
void
List<T>::clear()
{
    while(this->head)
        this->pop_front();
    this->sz = 0;
}

// Functions: selectors (get)

template<class T>
bool
List<T>::empty()
const noexcept
{
    return (!this->head && !this->tail);
}

template<class T>
T&
List<T>::front()
const noexcept
{
    return this->head->data;
}

template<class T>
T&
List<T>::back()
const noexcept
{
    return this->tail->data;
}

template<class T>
const unsigned long long&
List<T>::size()
const noexcept
{
    return this->sz;
}

template<class T>
typename List<T>::List_iterator
List<T>::begin()
const noexcept
{
    return List_iterator(this->head);
}

template<class T>
typename List<T>::List_iterator
List<T>::end()
const noexcept
{
    return List_iterator(this->tail->next);
}

template<class T>
typename List<T>::List_reverse_iterator
List<T>::rbegin()
const noexcept
{
    return List_reverse_iterator(this->tail);
}

template<class T>
typename List<T>::List_reverse_iterator
List<T>::rend()
const noexcept
{
    return List_reverse_iterator(this->head->prev);
}

// Operators overloads:

template<class T>
List<T>&
List<T>::operator = (const List<T>& other)
{
    this->clear();
    for (Node<T>* it = other.head; it; it = it->next)
        this->push_back(it->data);
    this->sz = other.size();
    return *this;
}

template<class T>
List<T>&
List<T>::operator = (std::initializer_list<T> ilist)
{
    this->clear();
    for (auto x : ilist)
        this->push_back(x);
    this->sz = ilist.size();
    return *this;
}

template<class T>
T&
List<T>::operator [] (const int& index)
{
    Node<T>* it = this->head;
    for (int i = 0; i < index; ++i)
        if (it->next)
        {
            it = it->next;
        }
        else
        {
            std::cerr << "ERROR: Going out of the list!\n";
            exit(1);
        }
    return it->data;
}

template<class T>
const T&
List<T>::operator [] (const int& index)
const
{
    Node<T>* it = this->head;
    for (int i = 0; i < index; ++i)
        if (it->next)
        {
            it = it->next;
        }
        else
        {
            std::cerr << "ERROR: Going out of the list!\n";
            exit(1);
        }
    return it->data;
}

template<class T>
std::ostream&
operator<<(std::ostream& os, const List<T>& li)
{
    os << '[';
    for (Node<T>* it = li.head; it; it = it->next)
        os << it->data << (it->next ? ", " : "");
    os << ']';
    return os;
}

// List_iterator constructors:

template<class T>
List<T>::List_iterator::List_iterator(Node<T>* p) :
ptr(p)
{}

// List_iterator operators overloads:

template<class T>
T&
List<T>::List_iterator::operator * ()
const noexcept
{
    return this->ptr->data;
}

template<class T>
Node<T>*
List<T>::List_iterator::operator -> ()
const noexcept
{
    return this->ptr;
}

template<class T>
List<T>::List_iterator::operator bool ()
const
{
    return this->ptr != nullptr;
}

template<class T>
typename List<T>::List_iterator&
List<T>::List_iterator::operator ++ ()
{
    this->ptr = this->ptr->next;
    return *this;
}

template<class T>
typename List<T>::List_iterator
List<T>::List_iterator::operator ++ (int)
{
    Node<T>* tmp = ptr;
    ++(*this);
    return List_iterator(tmp);
}

template<class T>
typename List<T>::List_iterator&
List<T>::List_iterator::operator -- ()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template<class T>
typename List<T>::List_iterator
List<T>::List_iterator::operator -- (int)
{
    Node<T>* tmp = ptr;
    --(*this);
    return List_iterator(tmp);
}

template<class T>
bool
List<T>::List_iterator::operator == (const List_iterator& other)
const noexcept
{
    return this->ptr == other.ptr;
}

template<class T>
bool
List<T>::List_iterator::operator != (const List_iterator& other)
const noexcept
{
    return this->ptr != other.ptr;
}

// List_reverse_iterator operators overloads:

template<class T>
typename List<T>::List_reverse_iterator&
List<T>::List_reverse_iterator::operator ++ ()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template<class T>
typename List<T>::List_reverse_iterator
List<T>::List_reverse_iterator::operator ++ (int)
{
    Node<T>* tmp = this->ptr;
    ++(*this);
    return List_iterator(tmp);
}

template<class T>
typename List<T>::List_reverse_iterator&
List<T>::List_reverse_iterator::operator -- ()
{
    this->ptr = this->ptr->next;
    return *this;
}

template<class T>
typename List<T>::List_reverse_iterator
List<T>::List_reverse_iterator::operator -- (int)
{
    Node<T>* tmp = this->ptr;
    --(*this);
    return List_iterator(tmp);
}
