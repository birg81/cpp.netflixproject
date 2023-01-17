#ifndef MEDIA_H
#define MEDIA_H

#include <sstream>
#include <string>
using namespace std;

class Media {
	protected:
		int id;
		string genre;
		string title;
		int n;
		char type;
	public:
		Media(int, char, string, string, int);
		int getId() const;
		char getType() const;
		string getGenre() const;
		string getTitle() const;
		void setGenre(string);
		void setTitle(string);
		string str() const;
};

Media::Media(
	int id = 0, char type = ' ',
	string genre = "GENRE", string title = "TITLE",
	int n = 0
) {
	this->id = id;
	this->type = type;
	this->genre = genre;
	this->title = title;
	this->n = n;
}
int Media::getId() const {
	return id;
}
char Media::getType() const {
	return type;
}
string Media::getGenre() const {
	return genre;
}
string Media::getTitle() const {
	return title;
}
void Media::setGenre(string genre = "") {
	if(genre.length() > 0) {
		this->genre = genre;
	}
}
void Media::setTitle(string title = "") {
	if(title.length() > 0) {
		this->title = title;
	}
}
string Media::str() const {
	stringstream s;
	s
		<< id << '\t'
		<< type << '\t'
		<< n << '\t'
		<< genre << '\t'
		<< title << '\n';
	return s.str();
}
#endif