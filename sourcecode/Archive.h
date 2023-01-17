#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "Movie.h"
#include "Serie.h"

#define FILE_MEDIA "medialist.txt"

#include <fstream>
#include <sstream>
#include <list>

using namespace std;

class Archive {
	protected:
		list<Movie> movies;
		list<Serie> series;
	public:
		Archive();
		void load();
		void save();
		bool isInMoviesList(string) const;
		bool isInSeriesList(string) const;
		void add(Movie);
		void add(Serie);
		Movie getMovieById(int);
		Serie getSerieById(int);
		string findSameMedia(string) const;
		string str() const;
};

Archive::Archive() {
	load();
}
void Archive::load() {
	ifstream f(FILE_MEDIA);
	while (!f.eof()) {
		int id;
		int n;
		string type = "";
		string title = "";
		string genre = "";
		f
			>> id
			>> type
			>> n
			>> genre
			>> title;
		if(type == "M") {
			Movie m = Movie(id, genre, title, n);
			add(m);
		}
		else if(type == "S") {
			Serie s = Serie(id, genre, title, n);
			add(s);
		} 
	}
	f.close();
}
void Archive::save() {
	ofstream f(FILE_MEDIA);
	if(movies.size() > 0) {
		for (auto& m : movies) {
			f
				<< m.getId() << "\tM\t"
				<< m.length() << '\t'
				<< m.getGenre() << '\t'
				<< m.getTitle() << '\n';
		}
	}
	if(series.size() > 0) {
		for (auto& s : series) {
			f
				<< s.getId() << "\tS\t"
				<< s.seasons() << '\t'
				<< s.getGenre() << '\t'
				<< s.getTitle() << '\n';
		}
	}
	f.close();
}
bool Archive::isInMoviesList(string name = "") const {
	if(movies.size() > 0) {
		for (auto& m : movies) {
			if(m.getTitle() == name) {
				return true;
			}
		}
	}
	return false;
}
bool Archive::isInSeriesList(string name = "") const {
	if(series.size() > 0) {
		for (auto& s : series) {
			if(s.getTitle() == name) {
				return true;
			}
		}
	}
	return false;
}
void Archive::add(Movie m) {
	if(!isInMoviesList(m.getTitle()) && m.getId() > 0){
		movies.push_back(m);
	}
}
void Archive::add(Serie s) {
	if(!isInSeriesList(s.getTitle()) && s.getId() > 0){
		series.push_back(s);
	}
}
Movie Archive::getMovieById(int idMovie = 0) {
	if(movies.size() > 0) {
		for(auto& m: movies) {
			if(m.getId() == idMovie) {
				return m;
			}
		}
	}
	return Movie(-1, "ERRORE", "TITLE", 0);
}
Serie Archive::getSerieById(int idSerie = 0) {
	if(series.size() > 0) {
		for(auto& s: series) {
			if(s.getId() == idSerie) {
				return s;
			}
		}
	}
	return Serie(-1, "ERRORE", "TITLE", 0);
}
string Archive::findSameMedia(string same = "") const {
	stringstream ss;
	list<Movie> mlist;
	list<Serie> slist;
	if(movies.size() > 0) {
		ss << "**************** MOVIES ****************\n";
		for(auto& m: movies){
			if((int)(m.str().find(same)) > -1) {
				mlist.push_back(m);
			}
		}
		if(mlist.size() == 0) {
			ss << "<<<<< NON CI CONO CORRISPONDENZE <<<<<<<\n";
		}
		else {
			for(auto& m: mlist){
				ss << m.str();
			}	
		}
	}
	if(series.size() > 0) {
		ss << "**************** SERIES ****************\n";
		for(auto& s: series){
			if((int)(s.str().find(same)) > -1) {
				slist.push_back(s);
			}
		}
		if(slist.size() == 0) {
			ss << "<<<<< NON CI CONO CORRISPONDENZE <<<<<<<\n";
		}
		else {
			for(auto& s: slist){
				ss << s.str();
			}	
		}
	}
	return ss.str();
}
string Archive::str() const {
	stringstream ss;
	if(movies.size() > 0) {
		ss
			<< "**************** MOVIES ****************\n"
			<< "ID\tType\tMIN\tGENRE\tTITLE\n";
		for (auto& m : movies) {
			ss << m.str();
		}
	}
	else {
		ss << "NON CI SONO FILM IN ELENCO!\n";
	}
	if(series.size() > 0) {
		ss
			<< "**************** SERIES ****************\n"
			<< "ID\tType\tS[]\tGENRE\tTITLE\n";
		for (auto& s : series) {
			ss << s.str();
		}
	}
	else {
		ss << "NON CI SONO SERIE IN ELENCO!\n";
	}
	return ss.str();
}
#endif