#include <cstddef>
#include <cstdarg>

template <typename T>
class SetElement
{
    T * value;
    SetElement<T> * nextElement;
public:
    SetElement(T _value)
    {
        value = new T;
        *value = _value;
        SetNextElement(NULL);
    }

    SetElement<T> * SetNextElement (SetElement<T> * element)
    {
        SetElement<T> * oldElement = nextElement;
        nextElement = element;
        return oldElement;
    }

    T Value()
    {
        return *value;
    }

    SetElement<T> * NextElement()
    {
        return nextElement;
    }
};

template <typename T>
class Set
{
    SetElement<T> * firstElement;
    int length;
public:
    Set()
    {
        firstElement = NULL;
        length = 0;
    }

    void Add(T value)
    {
        if(firstElement == NULL)
        {
            firstElement = new SetElement<T>(value);
            length++;
        }
        else
        {
            SetElement<T> * element = firstElement;
            while(element->Value() != value)
            {
                if(element->NextElement() == NULL)
                {
                    element->SetNextElement(new SetElement<T>(value));
                    length++;
                    return;
                }
                element = element->NextElement();
            }
        }
    }

    void Delete(T value)
    {
        SetElement<T> * element = firstElement;
        if(element == NULL)
            return;
        if(element->Value() == value)
        {
            if(element->NextElement() == NULL)
                firstElement = NULL;
            else
                firstElement = element->NextElement();
            delete element;
            length--;
            return;
        }
        if(element->NextElement() == NULL)
            return;
        while(element->NextElement()->Value() != value)
        {
            element = element->NextElement();
            if(element->NextElement() == NULL)
                return;
        }
        delete element->SetNextElement(element->NextElement()->NextElement());
        length--;
    }

    bool IsSet(T value)
    {
        SetElement<T> * element = firstElement;
        if(element == NULL)
            return false;
        while(element->Value() != value)
        {
            if(element->NextElement() == NULL)
                return false;
            element = element->NextElement();
        }
        return true;
    }

    void ForEach(void(*func)(T, va_list)...)
    {
        SetElement<T> * element = firstElement;
        while(element != NULL)
        {
            va_list args;
            va_start(args, func);
            func(element->Value(), args);
            element = element->NextElement();
            va_end(args);
        }
    }

    int Size()
    {
        return length;
    }
};