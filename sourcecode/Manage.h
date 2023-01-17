#ifndef MANAGE_H
#define MANAGE_H

#include "Account.h"

#define FILE_ACCOUNT "accountslist.txt"
#define MAX_SIGN_COUNT 3

class Manage {
	private:
		int accountSignId;
		int signCount;
		list<Account> accounts;
		bool add(Account);
	public:
		Manage();
		bool signin(string, string);	// login
		bool signup(string, string);	// registrazione
		void signout();			// logout
		bool isSigned();		// controlla se sei loggato
		bool isOverAttempts() const;	// controlla se ho superato i tentativi
		int existsAccountEmail(string);
		Account getAccount();
		string getAccountsList();
		void load();
		void save();
		string str();
};

Manage::Manage() {
	signCount = 0;
	signout();
	load();
}
bool Manage::add(Account a) {
	if(existsAccountEmail(a.getEmail()) < 0) {
		accounts.push_back(a);
		save();
		return true;
	}
	return false;
}
bool Manage::signin(string email = "", string password = "") {
	if(accounts.size() > 0 && email != "" && signCount < MAX_SIGN_COUNT) {
		for(auto& a : accounts) {
			if(a.getEmail() == email && a.checkPassword(password)) {
				signCount = 0;
				accountSignId = a.getId();
				return true;
			}
		}
	}
	signCount++;
	return false;
}
bool Manage::signup(string email = "", string password = "") {
	return add(Account(accounts.size() + 1, email, password));
}
void Manage::signout() {
	accountSignId = -1;
}
bool Manage::isSigned() {
	return signCount <= MAX_SIGN_COUNT && accountSignId > 0;
}
bool Manage::isOverAttempts() const {
	return signCount >= MAX_SIGN_COUNT;
}
int Manage::existsAccountEmail(string name = "") {
	if(accounts.size() > 0) {
		for(auto& a : accounts){
			if(a.getEmail() == name) {
				return a.getId();
			}
		}
	}
	return -1;
}
Account Manage::getAccount() {
	for(auto& a : accounts) {
		if(a.getId() == accountSignId) {
			return a;
		}
	}
	return Account(0, "Fake", "***");
}
string Manage::getAccountsList() {
	if(accounts.size() > 0) {
		stringstream ss;
		for(auto& a : accounts){
			ss << "\n* " << a.getEmail();
		}
		return ss.str();
	}
	return "\n!!! NON CI SONO ACCOUNT ATTIVI !!!!\n";
}
void Manage::load() {
	ifstream f(FILE_ACCOUNT);
	while (!f.eof()) {
		int idAccount;
		string email, password;
		f
			>> idAccount
			>> email
			>> password;
		if(idAccount > 0 && email != "") {
			Account a = Account(idAccount, email, password);
			add(a);
		}
	}
	f.close();
}
void Manage::save() {
	if(accounts.size() > 0) {
		ofstream f(FILE_ACCOUNT);
		for(auto& a : accounts) {
			f << a.str();
		}
		f.close();
	}
}
string Manage::str() {
	if(isSigned()) {
		return "Loggato!";
	}
	else if(signCount >= MAX_SIGN_COUNT){
		return "**** superato numero tentativi! ***";
	}
	else {
		return "*** RESTRICTED AREA ***";
	}
}
#endif