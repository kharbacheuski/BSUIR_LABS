#include <iostream>
#include <iterator>
#include <cstddef>
#define VALUE_ALREADY_EXIST_EXCEPTION "Value is already exist"
#define NEGATIVE_ANSWER 'n'
using namespace std;

template<class T>
class Node
{
private:
    Node<T>* next;
    T value;
public:
    T Value() { return value; }

    Node(T _val)
    {
        next = NULL;
        value = _val;
    }

    template<class T> friend class DoubleLinkedList;
};

template<class T>
class DoubleLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node<T>;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        Iterator& operator++() { m_ptr = m_ptr->next; return *this; }

        // Postfix increment
        Iterator operator++(int) { Iterator tmp = *this; m_ptr = m_ptr->next; return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    bool IsUniqueRequired;

    DoubleLinkedList(bool isUniqueRequired = false)
    {
        IsUniqueRequired = isUniqueRequired;
    }

    bool IsUnique(T data)
    {
        if (!IsUniqueRequired)
            return true;

        bool isExist = Find(data) != NULL;
        if (isExist)
            throw VALUE_ALREADY_EXIST_EXCEPTION;

        return !isExist;
    }

    void Push(T data)
    {
        if (!IsUnique(data))
            return;
        Node<T>* node = new Node<T>(data);

        if (head == NULL)
            head = node;
        else
        {
            tail->next = node;
        }
        count++;
    }

    void PushBegin(T data)
    {
        if (!IsUnique(data))
            return;
        Node<T>* node = new Node<T>(data);
        Node<T>* tmp = head;
        node->next = tmp;
        head = node;

        if (!count)
            tail = head;
        else
            tmp->prev = node;
        count++;
    }

    Node<T>* Find(T data)
    {
        Node<T>* current = head;
        while (current != NULL)
        {
            if (current->value == data)
                return current;
            current = current->next;
        }
        return NULL;
    }

    bool Remove(T data)
    {
        Node<T>* current = head;

        current = Find(data);

        if (current != NULL)
        {
            if (current->next != NULL)
                current->next->prev = current->prev;
            else
                tail = current->prev;

            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                head = current->next;
            count--;
            return true;
        }
        return false;
    }

    void Print()
    {
        for (auto i : *this)
            cout << i.value << " ";
        cout << endl;
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

template<class U>
void ClientType()
{
    rewind(stdin);
    cout << "do you need unique collection? (y/n)";
    bool isUniqueRequired = getchar() != NEGATIVE_ANSWER;

    DoubleLinkedList<U> arr = *(new DoubleLinkedList<U>(isUniqueRequired));

    U a;
    bool isEnd = false;
    try
    {
        while (!isEnd)
        {
            rewind(stdin);
            switch (getchar())
            {
            case 'a':
                rewind(stdin);
                cin >> a;
                arr.Push(a);
                break;
            case 'p':
                arr.Print();
                break;
            case 'f':
                rewind(stdin);
                cin >> a;
                (arr.Find(a) != NULL) ? cout << "exist" << endl : cout << "not exist" << endl;
                break;
            case 'd':
                rewind(stdin);
                cin >> a;
                arr.Remove(a);
                break;
            case 'q':
                isEnd = true;
                break;
            default:
                break;
            }
        }
    }
    catch (const char* msg)
    {
        if (!strcmp(msg, VALUE_ALREADY_EXIST_EXCEPTION))
            cout << VALUE_ALREADY_EXIST_EXCEPTION;
        terminate();
    }
}

int main()
{
    string type;

ne_rugaite_za_goto:
    cout << "input variable type: ";
    cin >> type;

    if (!type.compare("int"))
        ClientType<int>();
    else if (!type.compare("float"))
        ClientType<float>();
    else if (!type.compare("string"))
        ClientType<string>();
    else
        goto ne_rugaite_za_goto;

    return 0;
}