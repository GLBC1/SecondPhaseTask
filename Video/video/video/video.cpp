// video.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Video.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Video * myVideo = new Video("test.avi",0);
	myVideo->ShowVideo();
	
	delete myVideo;
	system("pause");
	return 0;
}



Video::Video( char* _fname, char _src, char _wndSize )
{
	this->vSrc = _src;	
	this->frame = 0;
	this->capture = 0;
	this->vFilename = NULL;

	this->wndSize = _wndSize;
	try
	{
		this->wndName = new char[FNAME_MAX_LEN];
	}
	catch (bad_alloc)
	{
		cout << "Cannot allocate memory for wndName\n";
	}
	if (_src == SRC_AVI)
	{	
		if ( _fname )
		{
			try
			{
				this->vFilename = new char[FNAME_MAX_LEN];
				strcpy(vFilename,_fname);
			}
			catch(std::bad_alloc)
			{
				cout << "Video::Video : Cannot allocate memory for filename\n";
			}
		}
		else
		{
			throw "Video::Video : _fname parametr is NULL\n";

		}
	}
}

Video::~Video(void)
{
	
	if ( vFilename != NULL )
	{
		delete vFilename;
		vFilename = NULL;
	}
	//cvReleaseImage(&frame);		//DUNNO HOW TO FIX IT!
	cvReleaseCapture(&capture);
	cvDestroyWindow(wndName);
	
}

int Video::LoadVideo( void )
{
	if (vSrc == SRC_AVI)
	{
		if ( CheckFileName() )
		{
			this->capture = cvCreateFileCapture( vFilename );

			if (capture)
			{	
				cout << "Video Stream loaded successfully\n";
				return 1;
			}
			else
			{
				throw "LoadVideo: Cannot load video from file\n";
			}
		}
	}
	else
	{
		// TODO load video from camera
		cout << "Load video from camera\n";
		return 1;
	}
	return 0;
}

void Video::CrWindow( char * _wndName )
{
	if(_wndName)
	{
		cvNamedWindow(_wndName,wndSize);
		strcpy(wndName,_wndName);
	}
	else if(CheckFileName())
	{
		cvNamedWindow(vFilename,wndSize);
		strcpy(wndName,vFilename);		// Make window name equal with filename
	}
	else
	{
		cvNamedWindow("Unnamed window",wndSize);
		strcpy(wndName,"Unnamed window");
	}
	
}

int Video::CheckFileName( void )
{
	if (vFilename)
	{
		return 1;	
	}
	else 
	{
		throw "Video file name is NULL \n";
	}
}

void Video::ShowVideo()
{
	try
	{
		
		LoadVideo();	// load our video (check for correct video file)
		CrWindow("test.avi");		// create window named as name of file
			
		while(1){				
			frame = cvQueryFrame( capture );

			if( !frame ) {
				throw "Cannot query frame from capture \n";
			}
				
			cvShowImage( wndName , frame );			// show image (video)

			char c = cvWaitKey(33);
			if (c == 27)		// if esc break video 
			{		
				break;
			}
		}	
		
	}
	catch(char * const exc)
	{
		cout << exc << endl;
	}
	
}
