#ifndef FEEDBACKMOVIES_H
#define FEEDBACKMOVIES_H

#include "Archive.h"
#include "FeedBackMedias.h"
#include <sstream>
#include <string>
using namespace std;

class FeedBackMovies: public FeedBackMedias {
	public:
		FeedBackMovies(int, int, int);
		string info();
		string str() const;
};
FeedBackMovies::FeedBackMovies(
	int fkProfile = 0, int fkMovie = 0, int feed = 0
):FeedBackMedias(fkProfile, fkMovie, feed) {
	mediaDB.load();
}
string FeedBackMovies::info() {
	Movie m = mediaDB.getMovieById(this->fkMedia);
	stringstream ss;
	string stars;
	switch (feed) {
		case 1: stars = "OOOO*"; break;
		case 2: stars = "OOO**"; break;
		case 3: stars = "OO***"; break;
		case 4: stars = "O****"; break;
		case 5: stars = "*****"; break;
		default: stars = "OOOOO"; break;
	}
	ss << stars << '\t' << m.str();
	return ss.str();
}
string FeedBackMovies::str() const {
	stringstream ss;
	ss
		<< fkProfile << "\tM\t"
		<< fkMedia << '\t'
		<< feed << '\n';
	return ss.str();
}
#endif