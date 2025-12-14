#include "FILE.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Book::Book(const string& file) : filename(file) {
    LoadFile();
}

bool Book::Add(const Contact& contact) {
    if (!contact.getCheck()) {
        cout << "ÄÀÍÍÛÅ ÍÅÊÎÐÐÅÊÒÍÛ!" << endl;
        return false;
    }
    contacts.push_back(contact);
    SaveFile();
    cout << "ÊÎÍÒÀÊÒ ÄÎÁÀÂËÅÍ" << endl;
    return true;
}

bool Book::Delete(const string& name, const string& surname) {
    auto it = remove_if(contacts.begin(), contacts.end(),
        [&](const Contact& c) {
            return c.getName() == name && c.getSurname() == surname;
        });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        SaveFile();
        cout << "ÊÎÍÒÀÊÒ ÓÄÀË¨Í!" << endl;
        return true;
    }
    cout << "ÒÀÊÎÃÎ ÊÎÍÒÀÊÒÀ ÍÅÒ!" << endl;
    return false;
}

bool Book::SaveFile() const {
    ofstream file(filename, ios::out | ios::trunc);

    if (!file) {
        cerr << "Îøèáêà: Íå óäàëîñü îòêðûòü ôàéë '" << filename << "' äëÿ çàïèñè!" << endl;
        return false;
    }

    int savedCount = 0;
    for (const auto& contact : contacts) {
        string line = ContactToString(contact);
        file << line << '\n';  
        if (file.fail()) {
            cerr << "Îøèáêà çàïèñè â ôàéë!" << endl;
            file.close();
            return false;
        }
        savedCount++;
    }
    file.close();

    if (!file) {
        cerr << "Îøèáêà ïðè çàêðûòèè ôàéëà!" << endl;
        return false;
    }
    cout << "Ñîõðàíåíî êîíòàêòîâ: " << savedCount << endl;
    return true;
}

bool Book::LoadFile() {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ôàéë íå íàéäåí." << endl;
        contacts.clear();
        return true; 
    }

    contacts.clear();
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            Contact contact = ContactFromString(line);
            if (contact.getCheck()) {
                contacts.push_back(contact);
                count++;
            }
        }
    }

    file.close();
    cout << "Çàãðóæåíî êîíòàêòîâ: " << count << endl;
    return true;
}

vector<Contact> Book::Search(const string& n) {
    vector<Contact> result;
    for (const auto& contact : contacts) {
        if (contact.getName().find(n) != string::npos ||
            contact.getSurname().find(n) != string::npos ||
            contact.getEmail().find(n) != string::npos) {
            result.push_back(contact);
        }
    }
    return result;
}

vector<Contact> Book::ALLContacts() const {
    return contacts;
}

void Book::ShowALL() const {
    cout << "Âñåãî êîíòàêòîâ: " << contacts.size() << endl;
    if (contacts.empty()) {
        cout << "ÊÎÍÒÀÊÒÎÂ ÍÅÒ" << endl;
        return;
    }
    cout << "ÂÑÅ ÊÎÍÒÀÊÒÛ:" << endl;
    for (size_t i = 0; i < contacts.size(); ++i) {
        const auto& contact = contacts[i];
        cout << i + 1 << ") " << contact.getSurname() << " "
            << contact.getName() << " " << contact.getMiddleName()
            << " - " << contact.getEmail() << endl;

        auto phones = contact.getAllPhones();
        for (const auto& phone : phones) {
            cout << "   " << phone.second << ": " << phone.first << endl;
        }
        cout << "   Àäðåñ: " << contact.getAdress() << endl;
        cout << "   Äàòà ðîæäåíèÿ: " << contact.getDateOfBirth() << endl;
        cout << "---" << endl;
    }
}

string Book::ContactToString(const Contact& contact) const {
    stringstream ss;
    ss << contact.getName() << "|" << contact.getSurname() << "|"
        << contact.getMiddleName() << "|" << contact.getEmail() << "|"
        << contact.getAdress() << "|" << contact.getDateOfBirth();

    auto phones = contact.getAllPhones();
    ss << "|";
    for (size_t i = 0; i < phones.size(); i++) {
        if (i > 0) ss << ";";
        ss << phones[i].first << ":" << phones[i].second;
    }
    return ss.str();
}

Contact Book::ContactFromString(const string& line) const {
    stringstream ss(line);
    string name, surname, middlename, email, address, date, phonesStr;

    // ×èòàåì âñå ïîëÿ
    getline(ss, name, '|');
    getline(ss, surname, '|');
    getline(ss, middlename, '|');
    getline(ss, email, '|');
    getline(ss, address, '|');
    getline(ss, date, '|');
    getline(ss, phonesStr);

    string firstPhone = "";
    PhoneType firstType = PhoneType::work;

    if (!phonesStr.empty()) {
        size_t semicolon = phonesStr.find(';');
        string firstPhoneEntry;

        if (semicolon != string::npos) {
            firstPhoneEntry = phonesStr.substr(0, semicolon);
        }
        else {
            firstPhoneEntry = phonesStr;
        }
        size_t colon = firstPhoneEntry.find(':');
        if (colon != string::npos) {
            firstPhone = firstPhoneEntry.substr(0, colon);
            string typeStr = firstPhoneEntry.substr(colon + 1);

            if (typeStr == "äîìàøíèé") firstType = PhoneType::home;
            else if (typeStr == "ñëóæåáíûé") firstType = PhoneType::official;
        }
        else {
            firstPhone = firstPhoneEntry;  // Åñëè íåò òèïà, áåðåì ïðîñòî íîìåð
        }
    }
    Contact contact(name, surname, email, firstPhone, firstType);
    contact.setMiddleName(middlename);
    contact.setAdress(address);
    contact.setDateOfBirth(date);

    return contact;
}