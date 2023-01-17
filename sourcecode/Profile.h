#ifndef PROFILE_H
#define PROFILE_H

#define FILE_FEEDS "feedbacklist.txt"

#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "FeedBackMovies.h"
#include "FeedBackSeries.h"

using namespace std;

class Profile {
	private:
		int id;	// ID Profilo
		string name;	// nome del profilo
		int fkAccount;	// riferimento al account
		list<FeedBackMovies> movies;	// film visti e votati
		list<FeedBackSeries> series;	// serie viste e votate
	public:
		Profile(int, int, string);
		int getId() const;
		string getName() const;
		void setName(string);
		void setFkAccount(int);
		bool setFeedBackToMovie(int, int);
		bool setFeedBackToSerie(int, int);
		string infoFeedBackMovie();
		string infoFeedBackSerie();
		void load();
		void save();
		string str() const;
};

Profile::Profile(int id = 0, int fkAccount = 0, string name = "Personal") {
	this->id = id;
	this->fkAccount = fkAccount;
	this->name = name;
	load();
}
int Profile::getId() const {
	return id;
}
string Profile::getName() const {
	return name;
}
void Profile::setName(string name = "Personal") {
	this->name = name;
}
void Profile::setFkAccount(int fkAccount = 1) {
	this->fkAccount = fkAccount;
}
bool Profile::setFeedBackToMovie(int idMovie = 0, int feed = 0) {
	if(feed < 1) {
		feed = 0;
	} else if(feed > 5) {
		feed = 5;
	}
	for(auto& m : movies) {
		if(m.getMediaId() == idMovie) {
			return false;
		}
	}
	FeedBackMovies m = FeedBackMovies(id, idMovie, feed); 
	movies.push_back(m);
	save();
	return true;
}
bool Profile::setFeedBackToSerie(int idSerie = 0, int feed = 0) {
	if(feed < 1) {
		feed = 0;
	} else if(feed > 5) {
		feed = 5;
	}
	for(auto& s : series) {
		if(s.getMediaId() == idSerie) {
			return false;
		}
	}
	FeedBackSeries s = FeedBackSeries(id, idSerie, feed);
	series.push_back(s);
	save();
	return true;
}
string Profile::infoFeedBackMovie() {
	if(movies.size() > 0) {
		stringstream ss;
		for(auto& m : movies) {
			ss << m.info();
		}
		return ss.str();
	}
	return "";
}
string Profile::infoFeedBackSerie() {
	if(series.size() > 0) {
		stringstream ss;
		for(auto& s : series) {
			ss << s.info();
		}
		return ss.str();
	}
	return "";
}
void Profile::load() {
	ifstream f(FILE_FEEDS);
	while (!f.eof()) {
		int idProfile, idMedia, feed;
		string type;
		f
			>> idProfile
			>> type
			>> idMedia
			>> feed;
		if(type == "M" && idProfile == id) {
			setFeedBackToMovie(idMedia, feed);
		}
		else if(type == "S" && idProfile == id) {
			setFeedBackToSerie(idMedia, feed);
		}
	}
	f.close();
}
void Profile::save() {
	if(movies.size() > 0 || series.size() > 0) {
		ifstream fi(FILE_FEEDS);
		list<FeedBackMovies> otherMovies;
		list<FeedBackSeries> otherSeries;
		while(!fi.eof()) {
			int idProfile, idMedia, feed;
			string type;
			fi
				>> idProfile
				>> type
				>> idMedia
				>> feed;
			if(type == "M" && idProfile != id) {
				FeedBackMovies m = FeedBackMovies(idProfile, idMedia, feed);
				otherMovies.push_back(m);
			}
			else if(type == "S" && idProfile != id) {
				FeedBackSeries s = FeedBackSeries(idProfile, idMedia, feed);
				otherSeries.push_back(s);
			}
		}
		fi.close();
		ofstream f(FILE_FEEDS);
		for(auto& m : otherMovies) {
			f << m.str();
		}
		for(auto& m : movies) {
			f << m.str();
		}
		for(auto& s : otherSeries) {
			f << s.str();
		}
		for(auto& s : series) {
			f << s.str();
		}
		f.close();
	}
}
string Profile::str() const {
	stringstream ss;
	ss
		<< fkAccount << '\t'
		<< id << '\t'
		<< name << '\n';
	return ss.str();
}
#endif