// Constructors:

template<class T>
list<T>::list()
{
    this->head = this->tail = nullptr;
    this->sz = 0;
}

template<class T>
list<T>::list(const list<T>& other) :
list()
{
    for (auto& x : other)
        this->push_back(std::move(x));

    this->sz = other.size();
}

template<class T>
list<T>::list(std::initializer_list<T> ilist) :
list()
{
    for (auto x : ilist)
        this->push_back(x);

    this->sz = ilist.size();
}

// Destructors:

template<class T>
list<T>::~list()
{
    while(this->head)
        this->pop_front();
}

// Methods:

template<class T>
void
list<T>::push_front(const T& x)
{
    node_t<T>* new_element = new node_t<T>;
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
list<T>::push_back(const T& x)
{
    node_t<T> * new_element = new node_t<T>;
    // FIXME: remove const_cast
    // (for now doesn't work with list<unique_ptr> without it)
    new_element->data = std::move(const_cast<T&>(x));
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
list<T>::emplace_front(ARGS&&... args)
{
    node_t<T>* new_element = new node_t<T>;
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
list<T>::emplace_back(ARGS&&... args)
{
    node_t<T>* new_element = new node_t<T>;
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
list<T>::pop_front()
{
    T data;
    if (!this->head)
    {
        std::cerr << "ERROR: List is already empty!";
        exit(EXIT_FAILURE);
    }

    if (this->head == this->tail)
    {
        data = std::move(this->head->data);
        this->head = this->tail = nullptr;
    }
    else
    {
        data = std::move(this->head->data);
        this->head = this->head->next;
        this->head->prev = nullptr;
    }
    
    --sz;
    return data;
}

template<class T>
const T
list<T>::pop_back()
{
    T data;
    if (!this->head)
    {
        std::cerr << "ERROR: List is already empty!";
        exit(EXIT_FAILURE);
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
list<T>::insert_after(List_iterator it, const T& x)
{
    node_t<T>* new_element = new node_t<T>;
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
typename list<T>::List_iterator
list<T>::find(const T& x)
const
{
    for (auto it = this->begin(); it; ++it)
        if (it->data == x)
            return it;
    return nullptr;
}

template<class T>
void
list<T>::erase(List_iterator it)
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
list<T>::clear()
{
    while(this->head)
        this->pop_front();
    this->sz = 0;
}

// Functions: selectors (get)

template<class T>
bool
list<T>::empty()
const noexcept
{
    return (!this->head && !this->tail);
}

template<class T>
T&
list<T>::front()
const noexcept
{
    return this->head->data;
}

template<class T>
T&
list<T>::back()
const noexcept
{
    return this->tail->data;
}

template<class T>
const unsigned long long&
list<T>::size()
const noexcept
{
    return this->sz;
}

template<class T>
typename list<T>::List_iterator
list<T>::begin()
const noexcept
{
    return List_iterator(this->head);
}

template<class T>
typename list<T>::List_iterator
list<T>::end()
const noexcept
{
    return List_iterator(this->tail->next);
}

template<class T>
typename list<T>::List_reverse_iterator
list<T>::rbegin()
const noexcept
{
    return List_reverse_iterator(this->tail);
}

template<class T>
typename list<T>::List_reverse_iterator
list<T>::rend()
const noexcept
{
    return List_reverse_iterator(this->head->prev);
}

// Operators overloads:

template<class T>
list<T>&
list<T>::operator = (const list<T>& other)
{
    this->clear();
    for (node_t<T>* it = other.head; it; it = it->next)
        this->push_back(it->data);
    this->sz = other.size();
    return *this;
}

template<class T>
list<T>&
list<T>::operator = (std::initializer_list<T> ilist)
{
    this->clear();
    for (auto x : ilist)
        this->push_back(x);
    this->sz = ilist.size();
    return *this;
}

template<class T>
T&
list<T>::operator [] (const int& index)
{
    node_t<T>* it = this->head;
    for (int i = 0; i < index; ++i)
        if (it->next)
        {
            it = it->next;
        }
        else
        {
            std::cerr << "ERROR: Going out of the list!\n";
            exit(EXIT_FAILURE);
        }
    return it->data;
}

template<class T>
const T&
list<T>::operator [] (const int& index)
const
{
    node_t<T>* it = this->head;
    for (int i = 0; i < index; ++i)
        if (it->next)
        {
            it = it->next;
        }
        else
        {
            std::cerr << "ERROR: Going out of the list!\n";
            exit(EXIT_FAILURE);
        }
    return it->data;
}

template<class T>
std::ostream&
operator<<(std::ostream& os, const list<T>& li)
{
    os << '[';
    for (node_t<T>* it = li.head; it; it = it->next)
        os << it->data << (it->next ? ", " : "");
    os << ']';
    return os;
}

// List_iterator constructors:

template<class T>
list<T>::List_iterator::List_iterator(node_t<T>* p) :
ptr(p)
{}

// List_iterator operators overloads:

template<class T>
T&
list<T>::List_iterator::operator * ()
const noexcept
{
    return this->ptr->data;
}

template<class T>
node_t<T>*
list<T>::List_iterator::operator -> ()
const noexcept
{
    return this->ptr;
}

template<class T>
list<T>::List_iterator::operator bool ()
const
{
    return this->ptr != nullptr;
}

template<class T>
typename list<T>::List_iterator&
list<T>::List_iterator::operator ++ ()
{
    this->ptr = this->ptr->next;
    return *this;
}

template<class T>
typename list<T>::List_iterator
list<T>::List_iterator::operator ++ (int)
{
    node_t<T>* tmp = ptr;
    ++(*this);
    return List_iterator(tmp);
}

template<class T>
typename list<T>::List_iterator&
list<T>::List_iterator::operator -- ()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template<class T>
typename list<T>::List_iterator
list<T>::List_iterator::operator -- (int)
{
    node_t<T>* tmp = ptr;
    --(*this);
    return List_iterator(tmp);
}

template<class T>
bool
list<T>::List_iterator::operator == (const List_iterator& other)
const noexcept
{
    return this->ptr == other.ptr;
}

template<class T>
bool
list<T>::List_iterator::operator != (const List_iterator& other)
const noexcept
{
    return this->ptr != other.ptr;
}

// List_reverse_iterator operators overloads:

template<class T>
typename list<T>::List_reverse_iterator&
list<T>::List_reverse_iterator::operator ++ ()
{
    this->ptr = this->ptr->prev;
    return *this;
}

template<class T>
typename list<T>::List_reverse_iterator
list<T>::List_reverse_iterator::operator ++ (int)
{
    node_t<T>* tmp = this->ptr;
    ++(*this);
    return List_iterator(tmp);
}

template<class T>
typename list<T>::List_reverse_iterator&
list<T>::List_reverse_iterator::operator -- ()
{
    this->ptr = this->ptr->next;
    return *this;
}

template<class T>
typename list<T>::List_reverse_iterator
list<T>::List_reverse_iterator::operator -- (int)
{
    node_t<T>* tmp = this->ptr;
    --(*this);
    return List_iterator(tmp);
}
