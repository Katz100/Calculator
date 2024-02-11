#ifndef DYARRAY_H
#define DYARRAY_H


#include <iostream>
#include <fstream>
#include <string>

#include <QDebug>

template<typename T>
class DyArray
{
private:


    int size;
    int max_size;
    T* array;
public:


    DyArray(int size);
    DyArray();
    DyArray(const DyArray& other);
    ~DyArray();

    int get_size() const;
    int get_max_size() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    void add(const T& value);
    void remove(int index);
    void write(const char* file_name);
    void read(const char* file_name);
    void swap(int a, int b);
    T remove_last();
    T remove_first();
    T topofstack();
    void clear();

    bool isOutOfBounds(int index) const;
    bool isEmpty() const;

};

template<typename T>
DyArray<T>::DyArray(int size) : size(size), max_size(size * 2), array(new T[max_size])
{
}

template<typename T>
DyArray<T>::DyArray() : size(0), max_size(2), array(new T[max_size])
{
}

template<typename T>
DyArray<T>::DyArray(const DyArray& other)
{

    size = other.size;
    max_size = other.max_size;

    T* temp_array = new T[max_size];

    for (int i = 0; i < size; i++)
    {
        temp_array[i] = other.array[i];
    }
    delete[] array;
    array = temp_array;
}

template<typename T>
DyArray<T>::~DyArray()
{
    delete[] array;
}





template<typename T>
void DyArray<T>::add(const T& value)
{
    if (size >= max_size)
    {
        max_size *= 2;
        T* temp_array = new T[max_size];

        for (int i = 0; i < size; i++)
        {
            temp_array[i] = array[i];
        }

        delete[] array;

        array = temp_array;
    }

    if (size > max_size)
    {
        throw std::invalid_argument("Array has overflowed");
    }
    array[size] = value;
    size++;
}

template<typename T>
void DyArray<T>::remove(int index)
{
    if (!isOutOfBounds(index))
    {
        throw std::invalid_argument("Index out of bounds");
    }
    T* temp_array = new T[max_size];


    for (int i = 0; i < index; i++)
    {
        temp_array[i] = array[i];
    }

    for (int i = index + 1; i < size; i++)
    {
        temp_array[i - 1] = array[i];
    }

    delete[] array;
    array = temp_array;
    size--;
}

template<typename T>
int DyArray<T>::get_size() const
{
    return size;
}

template<typename T>
int DyArray<T>::get_max_size() const
{
    return max_size;
}

template<typename T>
T& DyArray<T>::operator[](int index)
{

    if (!(isOutOfBounds(index)))
    {
        throw std::invalid_argument("Index out of bounds");
    }

    return array[index];
}

template<typename T>
const T& DyArray<T>::operator[](int index) const
{
    assert(isOutOfBounds(index) && "Array index out of bounds");

    return array[index];
}






template<typename T>
bool DyArray<T>::isOutOfBounds(int index) const
{
    return (index > -1 && index < max_size) ? 1 : 0;

}

template<typename T>
bool DyArray<T>::isEmpty() const
{
    return (size == 0);
}

template<typename T>
void DyArray<T>::write(const char* file_name)
{

    std::ofstream write_file(file_name);

    if (!write_file)
    {
        std::cerr << file_name << " could not be opened for writing.\n";
    }

    for (int i = 0; i < size; i++)
    {
        write_file << array[i] << ' ';
    }

    write_file.close();
}

template<typename T>
void DyArray<T>::read(const char* file_name)
{
    std::ifstream read_file(file_name);

    if (!read_file)
    {
        std::cerr << file_name << " could not be opended for reading.\n";
    }

    T value;

    while (read_file >> value)
    {
        add(value);
    }

    read_file.close();
}

template<typename T>
void DyArray<T>::swap(int a, int b)
{
   // assert(isOutOfBounds(a) && isOutOfBounds(b) && "Index out of bounds");
    T temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

template<typename T>
T DyArray<T>::remove_last()
{
    if (size <= 0)
    {
        throw std::invalid_argument("Array is empty");
    }
    T value = array[get_size() - 1];
    remove(get_size() - 1);
    return value;
}

template<typename T>
inline T DyArray<T>::remove_first()
{
    if (size <= 0)
    {
        throw std::invalid_argument("Array is empty");
    }
    T value = array[0];
    remove(0);
    return value;
}

template<typename T>
inline T DyArray<T>::topofstack()
{
    return array[get_size() - 1];
}

template<typename T>
void DyArray<T>::clear()
{
    //Get size of array before looping
    int n = get_size();
    for (int i = 0; i < n; i++)
    {
        //Removes first element and shifts following elements to the left by one.
        remove(0);
    }
}


template<typename T>
std::ostream& operator<<(std::ostream& ostr, const DyArray<T>& m)
{
    for (int i = 0; i < m.get_size(); i++)
    {
        ostr << m[i] << " ";
    }

    return ostr;
}

int precedence2(std::string op)
{
    char op2 = op[0];
    switch (op2)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '#':
        return 1;
    default:
        return 0;
    }
}

template<typename T, typename U>
auto perform(T op1, U op2, std::string token)
{
    char token2 = token[0];
    switch (token2)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op2 - op1;
    case '*':
        return op1 * op2;
    case '/':
        if (op1 == 0)
        {
            throw std::invalid_argument("Division by zero error");
        }
        return op2 / op1;
    default:
        throw std::invalid_argument("Invalid operator");
    }
}

double calculate(const std::string& name)
{

    DyArray<std::string> stack;
    DyArray<std::string> queue;


    std::size_t size = name.size();

    stack.add("#");

    for (std::size_t i = 0; i < size; i++)
    {
        std::string token;
        //operand case

        //check to see if there is a negative number and not a operator
        if (name[i] == '-' && (i == 0 || name[i-1] == '('))
        {
            token = '-';
            i++;
            while (i < size && (isdigit(name[i]) || name[i] == '.'))
            {

                token += name[i++];
                qDebug() << "token: " << token;

            }
            i--;
        }

        //check for positive numbers
        else if (isdigit(name[i]))
        {
            while (i < size && (isdigit(name[i]) || name[i] == '.'))
            {

                token += name[i++];
                qDebug() << "token2: " << token;

            }
            i--;
        }
        //operator case
        else
        {
            token = name[i];
        }
        //if first token is a digit, then rest of the token has to be a digit
        //or if first token is '-' followed by a digit, token has to be a negative number
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            queue.add(token);
        }
        else if (token == "(")
        {
            stack.add("(");
        }
        else if (token == ")")
        {
            std::string tmp = stack.remove_last();
            while (tmp != "(")
            {
                queue.add(tmp);
                tmp = stack.remove_last();
            }
        }
        else
        {
            while (precedence2(token) <= precedence2(stack.topofstack()))
            {
                std::string tmp = stack.remove_last();
                queue.add(tmp);
            }
            stack.add(token);
        }
    }

    while (stack.topofstack() != "#")
    {
        std::string tmp = stack.remove_last();
        queue.add(tmp);
    }

    DyArray<double> stack2;

    while (!(queue.isEmpty()))
    {
        std::string token = queue.remove_first();

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            stack2.add(stod(token));

        }
        else
        {

            auto operand1 = stack2.remove_last();
            auto operand2 = stack2.remove_last();
            auto result = perform(operand1, operand2, token);

            stack2.add(result);

        }

    }

    if (!stack2.isEmpty())
    {
    return stack2[0];
    }
    else
    {
        throw std::invalid_argument("Error, answer not found");
    }


}


#endif
