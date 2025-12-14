#include "CONTACT.h"

class Book {
private:
	vector<Contact> contacts;
	string filename;
public:
	size_t GetCount() const { return contacts.size();}
	Book(const string& file = "book.txt");
	bool Add(const Contact& contact);
	bool Delete(const string& name, const string& surname);
	bool SaveFile() const;
	bool LoadFile();
	vector<Contact> Search(const string& name);
	vector<Contact> ALLContacts() const;
	void ShowALL() const;
private:
	Contact ContactFromString(const string& line) const;
	string ContactToString(const Contact& contact) const;
};