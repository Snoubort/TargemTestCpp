#include <iostream>
#include <string>
#include "StringTestWork.h"
#include <list>

class String {
public:
    String(const char* charArr) {
        size = strlen(charArr);
        value = new char[size+1];
        for (int i = 0; i < size; i++) {
            value[i] = charArr[i];
        }
        value[size] = '\0';
    }
    String(const String& other)
    {
        this->size = other.size;
        this->value = new char[this->size+1];
        for (int i = 0; i < this->size; i++) {
            this->value[i] = other.value[i];
        }
        value[size] = '\0';
    }
    String(String&& moved) : value{moved.value} {
        size = moved.size;
        moved.value = nullptr;
        moved.size = 0;
    }
    ~String() {
        delete(value);
    }
    char* GetValue() {
        return value;
    }
    int GetSize() {
        return size;
    }

    String ToLower() {
        char* lowerStr = new char[this->size+1];
        for (int i = 0; i < this->size; i++) {
            lowerStr[i] = tolower(this->value[i]);
        }
        lowerStr[this->size] = '\0';
        String result(lowerStr);
        return result;
    }
    
    String& operator=(const String& other) {
        if (this->size == other.size) {
            for (int i = 0; i <= this->size; i++) {
                this->value[i] = other.value[i];
            }
        }
        else {
            this->size = other.size;
            this->value = new char[this->size+1];
            for (int i = 0; i < this->size; i++) {
                this->value[i] = other.value[i];
            }
        }
        this->value[this->size] = '\0';
        return *this;
    }
    String& operator=(const char* other) {
        if (this->size == strlen(other)) {
            for (int i = 0; i <= this->size; i++) {
                this->value[i] = other[i];
            }
        }
        else {
            this->size = strlen(other);
            this->value = new char[this->size+1];
            for (int i = 0; i < this->size; i++) {
                this->value[i] = other[i];
            }
            this->value[this->size] = '\0';
        }
        return *this;
    }
    String& operator+=(const String& other) { 
        this->size += other.size;
        char* newValue = new char[this->size];
        memcpy(newValue, this->value, this->size-other.size);
        memcpy(newValue+ this->size-other.size, other.value, this->size - other.size);
        this->value = new char[this->size+1];
        memcpy(this->value, newValue, this->size);
        this->value[this->size] = '\0';
        return *this;
    }
    String& operator+=(const char* other) {
        this->size += strlen(other);
        char* newValue = new char[this->size+1];
        memcpy(newValue, this->value, this->size - strlen(other));
        memcpy(newValue + this->size - strlen(other), other, strlen(other));
        this->value = new char[this->size+1];
        memcpy(this->value, newValue, this->size);
        this->value[this->size] = '\0';
        return *this;
    }
    friend String operator+(const String& left, const String& right) {
        char* newValue = new char[left.size + right.size + 1];
        memcpy(newValue, left.value, left.size);
        memcpy(newValue + left.size, right.value, right.size);
        newValue[left.size + right.size] = '\0';
        String result(newValue);
        delete[](newValue);
        return result;
    }
    friend String& operator+(const String& left, const char* right) {
        char* newValue = new char[left.size + strlen(right) + 1];
        memcpy(newValue, left.value, left.size);
        memcpy(newValue + strlen(right), right, strlen(right));
        newValue[left.size + strlen(right)] = '\0';
        String result(newValue);
        delete[](newValue);
        return result;
    }
    char operator[](int index) {
        return value[index];
    }
    bool operator>(String &other) {
        return strcmp((this->ToLower()).value, (other.ToLower()).value) > 0 ? true : false;
    }
    bool operator>(const char* other) {
        String otherS(other);
        return this > &otherS;
    }
    bool operator<(String &other) {
        return strcmp((this->ToLower()).value, (other.ToLower()).value) < 0 ? true : false;
    }
    bool operator<(const char* other) {
        String otherS(other);
        return this < &otherS;
    }
    bool operator==(String &other) {
        return strcmp((this->ToLower()).value, (other.ToLower()).value) == 0 ? true : false;
    }
    bool operator==(const char* other) {
        String otherS(other);
        return this == &otherS;
    }
    bool operator!=(String& other) {
        return !(*this==other);
    }
    bool operator!=(const char* other) {
        String otherS(other);
        return this != &otherS;
    }

private:
    int size = 0;
    char* value{};
};

std::ostream& operator<<(std::ostream& os, String outStr)
{
    for (int i = 0; i < outStr.GetSize(); i++) {
        os << outStr[i];
    }
    return os;
}
std::istream& operator>>(std::istream& is, String& inStr)
{
    char str[1000];
    std::cin.getline(str, 1000);
    inStr = str;
    return is;
}

using namespace std;
int main()
{
    cout << "Input strings:" << endl;
    String input("");
    list<String> sList;
    cin >> input;
    while (input.GetSize()>0) {
        sList.push_back(input);
        cin >> input;
    }
    cout << input << endl;

    sList.sort(greater<>());
    cout << "Reverse sorted list:" << endl;
    for (String i : sList) {
        cout << i << endl;
    }
}

