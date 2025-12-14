#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <ctime>

using namespace std;

enum class PhoneType {
    work,
    home,
    official
};

class Contact {
private:
    string Name;
    string MiddleName;
    string Surname;
    string Adress;
    string DateOfBirth;
    string Email;

    struct Phone {
        string number;
        PhoneType type;
        Phone(const string& number, PhoneType type);
    };

    vector<Phone> Phones;
    bool check;

public:
    Contact(const string& name, const string& surname,
        const string& email, const string& phone,
        PhoneType type = PhoneType::work);

    //геттеры
    string getName() const;
    string getSurname() const;
    string getEmail() const;
    string getMiddleName() const;
    string getAdress() const;
    string getDateOfBirth() const;
    bool getCheck() const;
    vector<pair<string, string>> getAllPhones() const;
    vector<string> getPhoneByType(PhoneType t) const;
    bool addNumber(const string& phone, PhoneType type = PhoneType::work);

    //сеттеры
    bool setName(const string& name);
    bool setSurname(const string& surname);
    bool setMiddleName(const string& middlename);
    bool setEmail(const string& email);
    bool setAdress(const string& adress);
    bool setDateOfBirth(const string& date);

private:
    string PhoneTypeToString(PhoneType t) const;

    // проверка данных
    static bool checkName(const string& name);
    static bool checkEmail(const string& e);
    static bool checkDateOfBirth(const string& date);
    static bool CheckPhone(const string& ph);

    //форматирование данных
    static string normName(const string& name);
    static string normEmail(const string& e);
    static string normPhone(const string& ph);
    static string removeSpace(const string& s);

    //дополнительные методы
    static bool Check_Letter(char a);
    static bool Check_English_Letter(char a);
    static int day_quantity(int m, int y);
};
