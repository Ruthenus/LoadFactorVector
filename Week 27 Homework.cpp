#include <iostream>
#include <windows.h>
#include <algorithm>
#include <ctime>

using namespace std;


class Vector
{
    unsigned int capacity = 10;     // максимальна кількість елементів
    int* data = new int[capacity];  // динамічний масив
    unsigned int length = 0;        // поточна кількість елементів

public:

    // Конструктор за замовчуванням
    Vector() {}


    // Додавання елемента в кінець масиву

    /*
    void AddToBack(int value)
    {
        if (length < capacity)
            data[length] = value;
        else {
            capacity *= 2;
            int* temp = new int[capacity];
            for (int i = 0; i < length; i++) {
                temp[i] = data[i];
            }
            temp[length] = value;
            delete[] data;
            data = temp;
        }
        length++;
    }
    */

    // Buffer overrun while writing to 'temp': the writable size 
    // is 'capacity*4' bytes, but 'length' bytes might be written.

    // https://learn.microsoft.com/en-us/cpp/code-quality/c6386?view=msvc-170

    void AddToBack(int value)
    {
        if (length >= capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            for (unsigned int i = 0; i < length; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
        if (length < capacity) {
            data[length] = value;
            ++length;
        }
    }


    // Додавання елемента на початок масиву

    /*
    void AddToFront(int value)
    {
        if (length < capacity) {
            for (int i = length - 1; i >= 0; i--) {
                data[i + 1] = data[i];
            }
            data[0] = value;
        }
        else {
            capacity *= 2;
            int* temp = new int[capacity];
            for (int i = 0; i < length; i++) {
                temp[i + 1] = data[i];
            }
            temp[0] = value;
            delete[] data;
            data = temp;
        }
        length++;
    }
    */

    // Buffer overrun while writing to 'temp':  the writable size 
    // is 'capacity*4' bytes, but '12' bytes might be written.

    void AddToFront(int value)
    {
        if (length >= capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            for (unsigned int i = length; i > 0; --i) {
                temp[i] = data[i - 1];
            }
            delete[] data;
            data = temp;
        }
        else {
            for (unsigned int i = length; i > 0; --i) {
                data[i] = data[i - 1];
            }
        }
        data[0] = value;
        ++length;
    }


    // Видалення останнього елемента
    void RemoveFromBack()
    {
        if (length == 0) {
            cout << "Масив пустий, видаляти НЕМА ЧОГО!\n";
            return;
        }
        --length;
    }


    // Видалення першого елемента
    void RemoveFromFront()
    {
        if (length == 0) {
            cout << "Масив пустий, видаляти НЕМА ЧОГО!\n";
            return;
        }
        for (unsigned int i = 1; i < length; ++i) {
            data[i - 1] = data[i];
        }
        --length;
    }


    // Вставка значення за індексом
    void Insert(int value, unsigned int index)
    {
        if (index > length) {
            cout << "Неправильний індекс!\n";
            return;
        }
        if (length >= capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            for (unsigned int i = 0; i < length; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
        for (unsigned int i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }


    // Видалення елемента за індексом
    void RemoveByIndex(unsigned int index)
    {
        if (length == 0) {
            cout << "Масив пустий, видаляти НЕМА ЧОГО!\n";
            return;
        }
        if (index >= length) {
            cout << "Неправильний індекс!\n";
            return;
        }
        for (unsigned int i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
    }


    // Видалення всіх елементів масиву із заданим значенням
    void RemoveByValue(int value)
    {
        unsigned int newLength = 0;
        for (unsigned int i = 0; i < length; i++) {
            if (data[i] != value) {
                data[newLength++] = data[i];
            }
        }
        length = newLength;
    }


    // Сортування масиву за зростанням
    void Sort()
        // https://cplusplus.com/reference/algorithm/sort/
    {
        sort(data, data + length);
    }


    // Зміна порядку елементів на зворотний
    void Reverse()
        // https://cplusplus.com/reference/algorithm/reverse/
    {
        reverse(data, data + length);
    }


    // Випадкове перемішування елементів
    void Shuffle()
        // https://cplusplus.com/reference/algorithm/random_shuffle/
    {
        random_shuffle(data, data + length);
    }


    // Очищення масиву (у main() задано протестувати 12 методів)
    void Clear()
    {
        for (unsigned int i = 0; i < length; ++i) {
            data[i] = 0;
        }
        length = 0;
    }


    // Виведення масиву в консоль
    void Print() const
    {
        if (length == 0) {
            cout << "Масив пустий!\n";
        }
        else {
            cout << "Ємність масиву: " << capacity << "\n";
            cout << "Кількість елементів: " << length << "\n";
            cout << "Елементи масиву: ";
            for (unsigned int i = 0; i < length; ++i)
            {
                cout << data[i] << " ";
            }
            cout << "\n";
        }
    }


    // ПРАВИЛО ТРЬОХ
    // https://en.cppreference.com/w/cpp/language/rule_of_three.html


    // Деструктор для звільнення пам'яті
    ~Vector()
    {
        cout << "D-TOR\n";
        if (data != nullptr) {
            delete[] data;
        }
    }


    // Конструктор копіювання
    Vector(const Vector& original)
    {
        cout << "COPY C-TOR\n";
        this->length = min(original.length, original.capacity);
        // this->length = original.length;
        this->capacity = original.capacity;
        this->data = new int[this->capacity];
        for (unsigned int i = 0; i < this->length; ++i)
            this->data[i] = original.data[i];
    }


    // Оператор присвоєння (copy-and-swap)
    Vector& operator=(Vector other)
    {
        cout << "Присвоєння за допомогою копіювання та обміну\n";
        swap(*this, other);
        return *this;
    }

    // Дружня функція для обміну двох Vector
    // https://en.cppreference.com/w/cpp/algorithm/swap.html
    friend void swap(Vector& a, Vector& b);


    // Дружні функції для потоків введення/виведення
    friend ostream& operator<<(ostream& os, const Vector& a);  // cout
    friend istream& operator>>(istream& is, Vector& a);        // cin


    // Доступ до елемента за індексом (не const)
    int& operator[](unsigned int index)
    {
        if (index >= length) cout << "Неправильний індекс!\n";
        return data[index];
    }


    // Доступ до елемента за індексом (const)
    const int& operator[](unsigned int index) const
    {
        if (index >= length) cout << "Неправильний індекс!\n";
        return data[index];
    }


    // Перевантаження оператора порівняння "дорівнює"
    bool operator==(const Vector& other) const
    {
        if (length != other.length) return false;
        for (unsigned int i = 0; i < length; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }


    // Перевантаження оператора порівняння "не дорівнює"
    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }

};


// Обмін ресурсами між двома Vector
void swap(Vector& a, Vector& b)
{
    using std::swap;
    swap(a.capacity, b.capacity);
    swap(a.length, b.length);
    swap(a.data, b.data);
}


// Перевантаження потоку << виведення 
ostream& operator<<(ostream& os, const Vector& a)
{
    os << "ДАНІ МАСИВУ\n";
    os << "Ємність: " << a.capacity << "\n";
    os << "Кількість елементів: " << a.length << "\n";
    os << "Елементи: ";

    for (unsigned int i = 0; i < a.length; ++i) {
        os << a.data[i] << " ";
    }
    os << "\n";

    return os;
}


// Перевантаження потоку >> введення
istream& operator>>(istream& is, Vector& a)
{
    cout << "На скільки елементів бажаєте створити масив? ";
    unsigned int count;
    is >> count;

    // Очистити поточний масив
    a.Clear();

    for (unsigned int i = 0; i < count; ++i)
    {
        int value;
        cout << "Елемент [" << i << "]: ";
        is >> value;
        a.AddToBack(value);
    }

    return is;
}


int main() {
    SetConsoleOutputCP(1251);
    srand(time(0));

    Vector a;
    cout << "\n=== Тестування AddToBack ===\n";
    a.AddToBack(21);
    a.AddToBack(23);
    a.AddToBack(25);
    a.AddToBack(29);
    a.AddToBack(35);
    a.Print();

    cout << "\n=== Тестування AddToFront ===\n";
    a.AddToFront(20);
    a.Print();

    cout << "\n=== Тестування RemoveFromBack ===\n";
    a.RemoveFromBack();
    a.Print();

    cout << "\n=== Тестування RemoveFromFront ===\n";
    a.RemoveFromFront();
    a.Print();

    cout << "\n=== Тестування Insert ===\n";
    a.Insert(24, 2);
    a.Print();

    cout << "\n=== Тестування RemoveByIndex ===\n";
    a.RemoveByIndex(3);
    a.Print();

    cout << "\n=== Тестування RemoveByValue ===\n";
    a.AddToBack(26);
    a.AddToBack(28);
    a.Print();
    a.RemoveByValue(26);
    a.Print();

    cout << "\n=== Тестування Sort ===\n";
    a.AddToBack(97);
    a.AddToBack(98);
    a.AddToBack(99);
    a.Print();
    a.Sort();
    a.Print();

    cout << "\n=== Тестування Reverse ===\n";
    a.Reverse();
    a.Print();

    cout << "\n=== Тестування Shuffle ===\n";
    a.Shuffle();
    a.Print();

    cout << "\n=== Тестування Clear ===\n";
    a.Clear();
    a.Print();

    cout << "\n=== Тестування конструктора копіювання та присвоєння ===\n";
    Vector b;
    b.AddToBack(100);
    b.AddToBack(101);
    Vector c = b;  // компілятор викликає конструктор копіювання
    c.Print();
    Vector d;
    d = c;         // оператор присвоєння
    d.Print();

    cout << "\n=== Тестування операторів порівняння ===\n";
    cout << "b == c: " << (b == c ? "Так" : "Ні") << "\n";
    cout << "b != c: " << (b != c ? "Так" : "Ні") << "\n";

    cout << "\n=== Тестування потоків введення/виведення ===\n";
    Vector e;
    cin >> e;   // введення через потік
    cout << e;  // виведення через потік

    cout << "\n=== Тестування оператора індексу ===\n";
    e[0] = 100;
    cout << "e[0]: " << e[0] << "\n";
    e.Print();

    return 0;
}