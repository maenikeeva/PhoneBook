#include "CONTACT.h"
using namespace std;


Contact::Phone::Phone(const string& number, PhoneType type)
    : number(number), type(type) {}

//конструктор
Contact::Contact(const string& name, const string& surname,
    const string& email, const string& phone,
    PhoneType type) : check(true) {

    if (!setName(name)) {
        check = false;
    }
    if (!setSurname(surname)) {
        check = false;
    }
    if (!setEmail(email)) {
        check = false;
    }
    if (!addNumber(phone, type)) {
        check = false;
    }

    MiddleName = "";
    Adress = "";
    DateOfBirth = "";
}

//геттеры
string Contact::getName() const {
    return this->Name;
}

string Contact::getSurname() const {
    return this->Surname;
}

string Contact::getEmail() const {
    return this->Email;
}

string Contact::getMiddleName() const {
    return this->MiddleName;
}

string Contact::getAdress() const {
    return this->Adress;
}

string Contact::getDateOfBirth() const {
    return this->DateOfBirth;
}

bool Contact::getCheck() const {
    return this->check;
}

vector<pair<string, string>> Contact::getAllPhones() const {
    vector<pair<string, string>> result;
    for (const auto& phone : Phones) {
        result.emplace_back(phone.number, PhoneTypeToString(phone.type));
    }
    return result;
}

vector<string> Contact::getPhoneByType(PhoneType t) const {
    vector<string> result;
    for (const auto& phone : Phones) {
        if (phone.type == t) {
            result.push_back(phone.number);
        }
    }
    return result;
}

bool Contact::addNumber(const string& phone, PhoneType type) {
    if (CheckPhone(phone)) {
        string upd_phone = normPhone(phone);
        Phones.emplace_back(upd_phone, type);
        return true;
    }
    return false;
}

//сеттеры
bool Contact::setName(const string& name) {
    if (checkName(name)) {
        Name = normName(name);
        return true;
    }
    return false;
}

bool Contact::setSurname(const string& surname) {
    if (checkName(surname)) {
        Surname = normName(surname);
        return true;
    }
    return false;
}

bool Contact::setMiddleName(const string& middlename) {
    if (middlename.empty() || checkName(middlename)) {
        MiddleName = normName(middlename);
        return true;
    }
    return false;
}

bool Contact::setEmail(const string& email) {
    if (checkEmail(email)) {
        Email = normEmail(email);
        return true;
    }
    return false;
}

bool Contact::setAdress(const string& adress) {
    Adress = adress;
    return true;
}

bool Contact::setDateOfBirth(const string& date) {
    if (checkDateOfBirth(date)) {
        DateOfBirth = date;
        return true;
    }
    return false;
}


string Contact::PhoneTypeToString(PhoneType t) const {
    switch (t) {
    case PhoneType::work: return "рабочий";
    case PhoneType::home: return "домашний";
    case PhoneType::official: return "служебный";
    }
}


bool Contact::checkName(const string& name) {
    if (name.empty()) return true;

    size_t start = name.find_first_not_of(" \t\n\r");
    if (start == string::npos) {
        return false;
    }

    string upd_name = removeSpace(name);
    if (upd_name.empty()) return false;
    if (!Check_Letter(upd_name[0])) {
        return false;
    }
    if (upd_name.back() == '-') {
        return false;
    }
    for (char c : upd_name) {
        if (!(Check_Letter(c) ???????????? c == '-' || c == ' ')) {
            return false;
        }
    }
    return true;
}
bool Contact::checkEmail(const string& e) {
    string email = removeSpace(e);
    if (email.empty()) return false;

    size_t dog = email.find('@');
    if (dog == string::npos ?????????? dog == email.length() - 1) {
        return false;
    }

    if (count(email.begin(), email.end(), '@') != 1) {
        return false;
    }
    string username = email.substr(0, dog);
    string right = email.substr(dog + 1);
    for (char a : username) {
        if (!Check_English_Letter(a) && !std::isdigit(a)) {
            return false;
        }
    }
    for (char a : right) {
        if (!Check_English_Letter(a) && !std::isdigit(a) && a != '.') {
            return false;
        }
    }
    return true;
}

bool Contact::checkDateOfBirth(const string& date) {
    string c = date;
    int dot_count = 0;
    for (char i : c) {
        if (i == '.') {
            dot_count++;
        }
    }
    if (dot_count != 2) {
        return false;
    }

    stringstream ss(c);
    string day, month, year;
    if (!getline(ss, day, '.') ?????????????????????????? !getline(ss, year, '.')) {
        return false;
    }
    auto is_digits = [](const string& s) {
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
        };
    if (!is_digits(day) ??????????????????? !is_digits(year)) {
        return false;
    }
    int d = stoi(day);
    int m = stoi(month);
    int y = stoi(year);
    if (y < 1900 || y > 2100) {
        return false;
    }
    if (m < 1 || m > 12) {
        return false;
    }
    int max_d = day_quantity(m, y);
    if (d < 1 || d > max_d) {
        return false;
    }
    time_t now = time(nullptr);
    tm* time = localtime(&now);
    int currentYear = time->tm_year + 1900;
    int currentMonth = time->tm_mon + 1;
    int currentDay = time->tm_mday;
    if (y > currentYear) {
        return false;
    }
    if (y == currentYear && m > currentMonth) {
        return false;
    }
    if (y == currentYear && m == currentMonth && d > currentDay) {
        return false;
    }
    return true;
}

bool Contact::CheckPhone(const string& ph) {
    if (ph.empty()) return false;
    if (ph[0] != '+' && ph[0] != '8') {
        return false;
    }
    bool brackets = false;
    string digits;
    for (size_t i = 0; i < ph.length(); i++) {
        char c = ph[i];
        if (isdigit(c)) {
            digits += c;
        }
        else if (c == '(') {
            if (brackets) return false;
            brackets = true;
        }
        else if (c == ')') {
            if (!brackets) return false;
            brackets = false;
        }
        else if (c == '-') {
        }
        else if (c != '+') {
            return false;
        }
    }
    if (digits.length() != 11) {
        return false;
    }
    return true;
}


string Contact::normName(const string& name) {
    return removeSpace(name);
}

string Contact::normEmail(const string& e) {
    return removeSpace(e);
}

string Contact::normPhone(const string& ph) {
    string result;
    for (char a : ph) {
        if (isdigit(a) || a == '+') {
            result += a;
        }
    }
    if (result.length() == 11 && result[0] == '8') {
        result = "+7" + result.substr(1);
    }
    return result;
}

string Contact::removeSpace(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos) {
        return "";
    }
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

bool Contact::Check_Letter(char a) {
    return (a >= 'A' && a <= 'Z') ????????????????????????
    (a >= '\xC0' && a <= '\xDF') ???????????????(a == '\xFF');
}

bool Contact::Check_English_Letter(char a) {
    return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
}
int Contact::day_quantity(int m, int y) {
    int days_per_month[] = { 0 };
    if (y % 4 == 0) {
        int days_per_month[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    }
    else {
        int days_per_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    }
    return days_per_month[m];
}