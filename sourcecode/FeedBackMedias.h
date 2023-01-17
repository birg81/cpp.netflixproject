#ifndef FEEDBACKMEDIAS_H
#define FEEDBACKMEDIAS_H

class FeedBackMedias {
	protected:
		Archive mediaDB;
		int
			fkProfile,
			fkMedia,
			feed;
	public:
		FeedBackMedias(int, int, int);
		int getProfileId() const;
		int getMediaId() const;
		int feedback() const;
		void feedback(int);
};
FeedBackMedias::FeedBackMedias(int fkProfile = 0, int fkMedia = 0, int feed = 0) {
	this->fkProfile = fkProfile;
	this->fkMedia = fkMedia;
	if(feed > 0 && feed <= 5) {
		this->feed = feed;
	}
	else {
		this->feed = 0;
	}
}
int FeedBackMedias::getProfileId() const {
	return fkProfile;
}
int FeedBackMedias::getMediaId() const {
	return fkMedia;
}
int FeedBackMedias::feedback() const {
	return feed;
}
void FeedBackMedias::feedback(int feed) {
	if(feed > 0 && feed <= 5) {
		this->feed = feed;
	}
}
#endif