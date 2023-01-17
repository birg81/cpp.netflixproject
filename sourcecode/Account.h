#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Profile.h"

#define MAX_PROFILES 4
#define FILE_PROFILES "profileslist.txt"

class Account {
	private:
		int id;
		string email;
		string password;
		list<Profile> profiles;
	public:
		Account(int, string, string);
		bool existsProfileName(string) const;
		bool add(Profile);
		bool add(string);
		Profile getProfileByName(string);
		void setPassword(string);
		int getId() const;
		string getEmail() const;
		bool checkPassword(string password) const;
		void load();
		void save();
		string printMyProfiles();
		string str() const;
};

Account::Account(int id = 0, string email = "fede@email.it", string password = "12345") {
	this->id = id;
	this->email = email;
	this->password = password;
	load();
}
bool Account::existsProfileName(string name = "") const {
	if(profiles.size() > 0) {
		for (auto const& p : profiles) {
			if(p.getName() == name) {
				return true;
			}
		}
	}
	return false;
}
bool Account::add(Profile p) {
	if(profiles.size() < MAX_PROFILES && !existsProfileName(p.getName())) {
		profiles.push_back(p);
		save();
		return true;
	}
	return false;
}
bool Account::add(string profilename = "") {
	Profile p = Profile(
		4 * id + profiles.size() -3,
		this->id, profilename
	);
	return profilename != "" && add(p);
}
Profile Account::getProfileByName(string name = "") {
	if(existsProfileName(name)) {
		for (auto const& p : profiles) {
			if(p.getName() == name) {
				return p;
			}
		}
	}
	return Profile(-1, -1, "ERRORE");
}
void Account::setPassword(string password = "") {
	if(password.length() > 0) {
		this->password = password;
	}
}
int Account::getId() const {
	return id;
}
string Account::getEmail() const {
	return email;
}
bool Account::checkPassword(string password) const {
	return this->password == password;
}
void Account::load() {
	ifstream f(FILE_PROFILES);
	while (!f.eof()) {
		int idAccount;
		int idProfile;
		string name;
		f
			>> idAccount
			>> idProfile
			>> name;
		if(idAccount == id) {
			Profile p = Profile(idProfile, id, name);
			add(p);
		}
	}
	f.close();
}
void Account::save() {
	if(profiles.size() > 0) {
		ifstream fi(FILE_PROFILES);
		list<Profile> otherProfiles;
		while (!fi.eof()) {
			int idAccount;
			int idProfile;
			string name;
			fi
				>> idAccount
				>> idProfile
				>> name;
			if(idAccount != this->id && name != "") {
				Profile p = Profile(idProfile, idAccount, name);
				otherProfiles.push_back(p);
			}
		}
		fi.close();
		ofstream f(FILE_PROFILES);
		for (auto& p : otherProfiles) {
			f << p.str();
		}
		for (auto& p : profiles) {
			f << p.str();
		}
		f.close();
	}
}
string Account::printMyProfiles() {
	if(profiles.size() > 0) {
		stringstream ss;
		for (auto& p : profiles) {
			ss << p.str();
		}
		return ss.str();
	}
	return "*** NON CI SONO PROFILI REGISTRATI ***\n";
}
string Account::str() const {
	stringstream ss;
	ss
		<< id << '\t'
		<< email << '\t'
		<< password << '\n';
	return ss.str();
}
#endif