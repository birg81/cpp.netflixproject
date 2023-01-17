#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"

class Movie: public Media {
	public:
		Movie(int, string, string, int);
		int length() const;
		void length(int);
};

Movie::Movie(
	int id = 0,
	string genre = "GENRE", string title = "TITLE",
	int length = 0
):Media(id, 'M', genre, title, length) {
	
}
int Movie::length() const {
	return n;
}
void Movie::length(int length) {
	this->n = length;
}
#endif