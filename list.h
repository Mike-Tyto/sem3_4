#include <iostream>

template <typename T>
class Node {
    public:
    T value;
    Node<T>* next;

    Node(const T& value) {
        this->value = value;
        this->next = nullptr;
    }
};

template <typename T>
class LinkedList {
    private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size;

    public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
        // std::cout << "default constr\n";
    }

    LinkedList(T* items, size_t size) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        for (int i = 0; i < size; i++) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& linkedList) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        for (int i = 0; i < linkedList.size; i++) {
            T val = linkedList.Get(i);
            Append(val);
        }
    }

    //    template <typename... Args>
    //    LinkedList (T head, Args... args) {
    //        this->head = nullptr;
    //        this->tail = nullptr;
    //        this->size = 0;

    //        this->Append(head);

    //        ((this->Append(args)), ...);
    //    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    class ListIterator {
private:
        Node<T>* current;

public:
        ListIterator()
            : current(nullptr) {
        }

        ListIterator(Node<T>* node)
            : current(node) {
        }

        ListIterator& operator++() {
            current = current->next;

            return *this;
        }

        T& operator*() const {
            return current->value;
        }

        bool operator==(const ListIterator& other) const {
            return this->current == other.current;
        }

        bool operator!=(const ListIterator& other) const {
            return this->current != other.current;
        }
    };

    using Iterator = LinkedList<T>::ListIterator;

    Iterator begin() {
        if (head == nullptr) {
            return ListIterator(nullptr);
        }
        return ListIterator(this->head);
    }

    Iterator end() {
        return ListIterator(nullptr);
    }

    size_t GetLength() const noexcept {
        return size;
    }

    bool IsEmpty() const noexcept {
        return size == 0;
    }

    void Append(const T& value) noexcept {
        Node<T>* node = new Node<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void Prepend(const T& value) noexcept {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
        size++;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            Prepend(value);
        } else if (index == size) {
            Append(value);
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node<T>* node = new Node<T>(value);
            node->next = current->next;
            current->next = node;
            size++;
        }
    }

    T& Get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    T& GetFirst() const {
        if (this->IsEmpty()) {
            throw std::out_of_range("Index out of range");
        }
        return head->value;
    }

    T& GetLast() const {
        if (this->IsEmpty()) {
            throw std::out_of_range("Index out of range");
        }
        return tail->value;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex >= this->GetLength()) {
            throw std::out_of_range("Index out of range");
        }

        LinkedList* res = LinkedList();
        for (int i = startIndex; i < endIndex; i++) {
            res->Append(this->Get(i));
        }
        return res;
    }

    LinkedList<T>* Concat(LinkedList<T>* list) {
        LinkedList<T>* res = new LinkedList<T>();

        for (int i = 0; i < this->GetLength(); i++) {
            res->Append(this->Get(i));
        }

        for (int i = 0; i < list->GetLength(); i++) {
            res->Append(list->Get(i));
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        if (list.IsEmpty()) {
            os << "[]";
        }

        else {
            os << "[";

            for (size_t i = 0; i < list.size - 1; i++) {
                os << list.Get(i) << ", ";
            }
            os << list.Get(list.size - 1) << "]";
        }

        return os;
    }

    bool operator==(const LinkedList<T>& list) {
        if (this->size != list.GetLength()) {
            return 0;
        }

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != list.Get(i)) {
                return 0;
            }
        }

        return 1;
    }

    auto& operator[](const int index) const {
        return Get(index);
    }

    void Remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            if (tail == temp) {
                tail = nullptr;
            }
            delete temp;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            if (tail == temp) {
                tail = current;
            }
            delete temp;
        }
        size--;
        if (size == 0) {
            head = nullptr;
            tail = nullptr;
        }
    }
};
