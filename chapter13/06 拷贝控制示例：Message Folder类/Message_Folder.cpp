#include <iostream>
#include <set>
#include <string>
#include <vector>

using std::string; using std::vector; using std::set; using std::ostream; using std::cout;

class Folder;
class Message {
	friend void swap(Message&, Message&);
	friend ostream& print(ostream&, const Message&);
public:
	explicit Message(const string& str = "") : content(str) {}
	Message(const Message& m) : content(m.content), folders(m.folders)
	{
		add_to_Folders(m);
	}
	Message& operator=(const Message&);
	~Message() { remove_from_Folders(); }
	void save(Folder&);
	void remove(Folder&);
	void addFolder(Folder* f) { folders.insert(f); }
	void remFolder(Folder* f) { folders.erase(f); }
private:
	string content;
	set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
};

// copy-control functions
Message&
Message::operator=(const Message& rhs)
{
	remove_from_Folders();
	content = rhs.content;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

class Folder {
	friend ostream& print(ostream&, const Folder&);
public:
	Folder(const string& str = ".") : name(str) {}
	Folder(const Folder& f) : name(f.name), messages(f.messages) { add_to_Messages(f); }
	Folder& operator=(const Folder&);
	~Folder() { remove_from_Messages(); }
	void addMsg(Message* m) { messages.insert(m); }
	void remMsg(Message* m) { messages.erase(m); }
private:
	string name;
	set<Message*> messages;
	void add_to_Messages(const Folder&);
	void remove_from_Messages();
};

// copy-control functions
Folder&
Folder::operator=(const Folder& rhs)
{
	remove_from_Messages();
	name = rhs.name;
	messages = rhs.messages;
	add_to_Messages(rhs);
	return *this;
}

// member functions
void
Folder::add_to_Messages(const Folder& f)
{
	for (auto m : f.messages)
		m->addFolder(this);
}

void
Folder::remove_from_Messages()
{
	for (auto m : messages)
		m->remFolder(this);
}

void
Message::save(Folder& f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void
Message::remove(Folder& f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void
Message::add_to_Folders(const Message& m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

void
Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);
}

void swap(Message& lhs, Message& rhs)
{
	using std::swap;      // good practice
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.content, rhs.content);
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

// non-members functions
ostream& print(ostream& os, const Message& m)
{
	os << m.content << '\n';
	for (const auto f : m.folders)
		cout << f << ' ';
	return os;
}

ostream& print(ostream& os, const Folder& f)
{
	os << f.name << '\n';
	for (const auto m : f.messages)
		cout << m << ' ';
	return os;
}

int main()
{
	vector<Folder> dir{ {"Inbox"}, {"News"}, {"Important"}, {"Old"}, {"Junk"}, {"Trash"} };
	Message msg1("Meeting at 2:30 PM"), msg2("Let's ski tomorrow!"),
		msg3("Don't forget tonight"), msg4("Buy 2, get the third for free"),
		msg5("overdue balance");

	msg1.save(dir[0]);
	msg2.save(dir[0]);
	msg3.save(dir[0]);
	msg4.save(dir[0]);
	msg5.save(dir[0]);

	msg1.save(dir[2]);
	msg2.save(dir[3]);
	msg3.save(dir[2]);
	msg4.save(dir[4]);
	msg5.save(dir[5]);

	for (const auto& d : dir)
		print(cout, d) << '\n';

	return 0;
}
