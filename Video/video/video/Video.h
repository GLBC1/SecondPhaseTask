#ifndef _VIDEO_H
#define _VIDEO_H



#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define FNAME_MAX_LEN 50

using namespace std;

class Video
{
public:
	Video(char* _fname, char _src = SRC_AVI, char _wndSize = CV_WINDOW_AUTOSIZE);
	~Video();
	void ShowVideo();
	CvCapture* capture;
	IplImage* frame;
	

private:
	char* vFilename;
	char vSrc;		// AVI = 1 , CAM = 0

	char* wndName;
	char wndSize;
	
	
	
	enum captureSrc		
	{
		SRC_CAM,
		SRC_AVI
	};

	Video(void);
	int CheckFileName( void );
	int LoadVideo( void );
	void CrWindow( char * _wndName );
};

#endif
