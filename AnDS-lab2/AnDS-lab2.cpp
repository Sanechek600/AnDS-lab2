#include <iostream>
#include <stdexcept>

template<class T>
class DoublyLinkedList
{
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node* head, * tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    DoublyLinkedList(const DoublyLinkedList<T>& dll) {
        head = nullptr;
        Node* tmp = dll.head;
        while (tmp) {
            push_back(tmp->data);
            tmp = tmp->next;
        }
    }
    DoublyLinkedList& operator=(const DoublyLinkedList& dll) {
        if (this == &dll) {
            return *this;
        }
        this->~DoublyLinkedList();
        Node* tmp = dll.head;

        while (tmp) {
            push_back(tmp->data);
            tmp = tmp->next;
        }

        return *this;
    }

    ~DoublyLinkedList()
    {
        Node* tmp = nullptr;
        while (head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
    }

    T& operator[](const int index) {
        if (index < 0) throw std::out_of_range("Op.[] out of range, index<0");

        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        if (tmp) {
            return tmp->data;
        }
        else {
            throw std::out_of_range("Op.[] out of range, index>len");
        }
        
    }

    T& operator[](const int index) const {
        if (index < 0) throw std::out_of_range("Op.[] out of range, index<0");

        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }

    void push_front(T val)
    {
        Node* node = new Node(val);
        Node* tmp = head;
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head = node;
            node->next->prev = node;
        }
    }

    void push_front(const DoublyLinkedList& dll) 
    {
        Node* tmp = dll.tail;
        while (tmp) {
            push_front(tmp->data);
            tmp = tmp->prev;
        }
    }

    void push_back(T val)
    {
        Node* node = new Node(val);
        if (tail == nullptr) {
            head = node;
            tail = node;
        }else{
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void push_back(const DoublyLinkedList& dll)
    {
        Node* tmp = dll.head;
        while (tmp) {
            push_back(tmp->data);
            tmp = tmp->next;
        }
    }

    void pop_head() 
    {
        if (head) {
            Node* tmp = head;
            head = head->next;
            head->prev = nullptr;
            delete tmp;
        }else return;
    }

    void pop_tail()
    {
        if (tail) {
            Node* tmp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete tmp;
        }else return;
    }

    void delete_node(T val)
    {
        if (!head) return;

        Node* find = find_node(val);
        if (find == nullptr) return;

        Node* tmp = head;

        if (tmp == find)
        {
            head = tmp->next;
        }
        else
        {
            while (find != nullptr)
            {
                if (tmp->next == find)
                {
                    if (find->next) {
                        tmp->next = find->next;
                        find->next->prev = tmp;
                    }
                    else {
                        tmp->next = nullptr;
                    }
                    delete find;
                    break;
                }
                tmp = tmp->next;
            }
        }
        delete_node(val);
    }

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<U>& dll) {
        dll.display(os);
        return os;
    }

    //
    // Task realization
    //

    int numerize() const {
        int res = 0, dec_mul = 1;
        Node* tmp = tail;
        while (tmp) {
            res += (tmp->data * dec_mul);
            dec_mul = dec_mul * 10;
            tmp = tmp->prev;
        }
        return res;
    }

    int sum(const DoublyLinkedList<T>& dll) {
        return numerize() + dll.numerize();
    }

    int composition(const DoublyLinkedList<T>& dll) {
        return numerize() * dll.numerize();
    }

private:

    Node* find_node(T n) //returns node of the given number
    {
        Node* node = head;
        while (node != nullptr)
        {
            if (node->data == n)
                return node;

            node = node->next;
        }
        std::cerr << "No such element in the list \n";
        return nullptr;
    }

    void display(std::ostream& out = std::cout) const
    {
        Node* node = head;
        while (node != nullptr)
        {
            out << node->data;
            node = node->next;
        }
    }
};

int main() {
    DoublyLinkedList<int> l1;
    l1.push_front(3);
    l1.push_back(5);
    l1.push_back(1);
    l1.push_front(6);
    l1.push_back(8);

    std::cout << l1 << "\n";
    std::cout << "l1[2]: " << l1[2] << "\n";
    l1.delete_node(1);
    std::cout << l1 << "\n";
    l1.pop_head();
    std::cout << l1 << "\n";
    l1.pop_tail();
    std::cout << l1 << "\n\n";

    DoublyLinkedList<int> l2;
    l2.push_back(1);
    l2.push_back(0);
    l2.push_back(0);
    l2.push_back(0);
    l2.push_back(0);
    l2.push_back(1);

    std::cout << l1.sum(l2) << "\n";
    std::cout << l1.composition(l2) << "\n\n";

    l2.delete_node(0);
    std::cout << l2 << "\n";
    return 0;
}