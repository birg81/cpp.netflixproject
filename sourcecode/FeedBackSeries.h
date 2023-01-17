#ifndef FEEDBACKSERIES_H
#define FEEDBACKSERIES_H

#include "Archive.h"
#include "FeedBackMedias.h"
#include <sstream>
#include <string>
using namespace std;

class FeedBackSeries: public FeedBackMedias {
	public:
		FeedBackSeries(int, int, int);
		string info();
		string str() const;
};
FeedBackSeries::FeedBackSeries(
	int fkProfile = 0, int fkSerie = 0, int feed = 0
):FeedBackMedias(fkProfile, fkSerie, feed) {
	mediaDB.load();
}
string FeedBackSeries::info() {
	Serie s = mediaDB.getSerieById(this->fkMedia);
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
	ss << stars << '\t' << s.str();
	return ss.str();
}
string FeedBackSeries::str() const {
	stringstream ss;
	ss
		<< fkProfile << "\tS\t"
		<< fkMedia << '\t'
		<< feed << '\n';
	return ss.str();
}
#endif