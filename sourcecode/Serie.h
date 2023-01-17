#ifndef SERIE_H
#define SERIE_H

#include "Media.h"

class Serie: public Media {
	public:
		Serie(int, string, string, int);
		int seasons() const;
		void seasons(int);
};

Serie::Serie(
	int id = 0,
	string genre = "GENRE", string title = "TITLE",
	int seasons = 0
):Media(id, 'S', genre, title, seasons) {
	// vuoto
}
int Serie::seasons() const {
	return n;
}
void Serie::seasons(int seasons) {
	this->n = seasons;
}
#endif