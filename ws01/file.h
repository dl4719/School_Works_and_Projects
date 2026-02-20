#ifndef SENECA_FILE_H_
#define SENECA_FILE_H_
namespace seneca {

	bool openFile(const char filename[]);
	void closeFile();
	bool readTitle(char title[]);
	bool readYear(int* year);
	bool readMovieRating(char rating[]);
	bool readDuration(int* duration);
	bool readGenres(char genres[][11]);
	bool readConsumerRating(float* rating);
}
#endif // !SENECA_FILE_H_

