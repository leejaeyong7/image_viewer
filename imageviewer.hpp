#ifndef _IMAGE_VIEWER
#define _IMAGE_VIEWER

//set window values
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


//includes
#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>
#include <FL/Fl_Gl_Window.H>
#include <JMD_Vision_Image.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
using namespace std;
using namespace JMD;
using namespace cv;

typedef void(*CallbackFunctionPtr)(int*);

class Image_Viewer : public Fl_Gl_Window
{
	public:
	
	//default constructors
		Image_Viewer(const char* name = 0, int numScrn =0 ,CallbackFunctionPtr cb = NULL,int *p = NULL, int wWidth =WINDOW_WIDTH , int wHeight = WINDOW_HEIGHT)
		:Fl_Gl_Window(WINDOW_X, WINDOW_Y, wWidth, wHeight, name)
		{
			m_cb = cb;
			m_p = p;
			dInit = false;
			numberOfScreens = numScrn;
			window_Width = wWidth;
			window_Height = wHeight;
			
			//imageOrVideo is true if image, false if video viewer
			if (m_cb==NULL && m_p==NULL)
			{
				cout<<"image viewer"<<endl;
				imageOrVideo = true;
				imageArray = new JMD_Vision_Image*[numScrn];
				gluImageInt = new GLuint[numScrn];
				for(int i = 0; i<numScrn; i++)
				{
					imageArray[i] = NULL;
					//gluImageInt[i] = 0;
				}
			}
			else
			{
				cout<<"video viewer"<<endl;
				imageOrVideo = false;
				Fl::add_timeout(1.0/30.0, Timer_CB, (void*)this);
			}
			
		}
	
	
		void draw();
		int handle(int event);
	
	
		void addImages(JMD_Vision_Image * image, int screenNumber);
		void addVideo(JMD_Vision_Image* videostream);
		void runfunction();
	
	
	private:
		//window handling values
		int window_Height;
		int window_Width;
	
	
	
		//private values
		CallbackFunctionPtr m_cb;
		int* m_p;
		int numberOfScreens;
	
		//redraw variables
		static void Timer_CB(void *userdata)
		{
			Image_Viewer *win = (Image_Viewer*)userdata;
			win->redraw();
			Fl::repeat_timeout(1.0/30.0, Timer_CB, userdata);
		}
	
		//control variables
		bool dInit;
		bool imageOrVideo;
	
		//Video variables
		JMD_Vision_Image * video;
		GLuint cameraImageTextureID;
	
		//JMD vision Image variables
		JMD_Vision_Image ** imageArray;
		GLuint * gluImageInt;
	
	
		//coordinate parameter
		float xc;
		float yc;
		float xw;
		float yw;
		float boxRatio;
		float imgRatio;
	
};

////////////////////////////////////////////////////////////////////////////
//						Class Implementation							  //
////////////////////////////////////////////////////////////////////////////
void Image_Viewer::draw()
{
	//initializes drawing elements
	if(!dInit)
	{
		cout<<"initializing..."<<endl;
		dInit = true;
		glClearDepth(1.0f);
		glClearColor(0.75, 0.75, 0.75, 0);
		
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

	}
	//glLoadIdentity();
	if (imageOrVideo)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (int i = 0; i< numberOfScreens; i++ )
		{
			//division/scale factor
			int NUMOFIMGX = ceil(sqrt(numberOfScreens));
			xc = (((float)2/NUMOFIMGX) * (i%NUMOFIMGX) -1);
			yc = ((float)2/ceil((float)numberOfScreens/NUMOFIMGX) * (i/NUMOFIMGX)  -1);
			xw = ((float)2/NUMOFIMGX);
			yw = ((float)2/ceil((float)numberOfScreens/NUMOFIMGX));
			
		
			
			
			//case if there is image
			if (imageArray[i]!=NULL)
			{
				boxRatio = ((float)(window_Height/ceil((float)numberOfScreens/NUMOFIMGX))/(window_Width/NUMOFIMGX));
				imgRatio = ((float)imageArray[i]->Height()/imageArray[i]->Width());
				
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, gluImageInt[i]);
				
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				switch (imageArray[i]->myTypes())
				{
					//char
					case 0:
					{
						if (imageArray[i]->Channels()==3)
						{
							glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_UNSIGNED_BYTE, imageArray[i]->Data());
						}
						else if(imageArray[i]->Channels()==1)
						{
							glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
							glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_UNSIGNED_BYTE, imageArray[i]->Data());
						}
						break;
					}
					//short
					case 1:
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_SHORT, imageArray[i]->Data());
						break;
					}
					//int
					case 2:
					{
						
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_INT, imageArray[i]->Data());
						break;
					}
					//float
					case 3:
					{
						glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_FLOAT, imageArray[i]->Data());
						break;
					}
					//double
					case 4:
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,imageArray[i]->Height(), imageArray[i]->Width(), 0, GL_BGR, GL_DOUBLE, imageArray[i]->Data());
						break;
					}
					default:
					{
						cout<<"error no correct image format"<<endl;
						break;
					}
				}
				glBindTexture(GL_TEXTURE_2D, gluImageInt[i]);
				glColor3f(1,1,1);
				if (boxRatio>imgRatio)
				{
					float hd = (yw - (yw/boxRatio))/2;
					glBegin(GL_QUADS);
					{
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(	xc,
								   -(yc + hd),
								   0.0f);
						
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f( xc+xw,
								   -(yc+hd),
								   0.0f);
						
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(	xc+xw,
								   -(yc+yw-hd),
								   0.0f);
						
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(	xc,
								   -(yc+yw-hd),
								   0.0f);
					}
					glEnd();

				}
				else
				{
					float xd = (xw - (xw*boxRatio))/2;
					glBegin(GL_QUADS);
					{
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(	xc+xd,
								   -yc,
								   0.0f);
						
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f( xc+xw-xd,
								   -yc,
								   0.0f);
						
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(	xc+xw-xd,
								   -(yc+yw),
								   0.0f);
						
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(	xc+xd,
								   -(yc+yw),
								   0.0f);
					}
					glEnd();

				}
				glDisable(GL_TEXTURE_2D);
				
			}
			glColor3f(0,0,0);
			glLineWidth(0.5);
			glBegin(GL_LINES);
			{
				glVertex3f(	xc,
						   -yc,
						   0.0f);
				glVertex3f( xc+xw,
						   -yc,
						   0.0f);
				
				glVertex3f( xc+xw,
						   -yc,
						   0.0f);
				glVertex3f(	xc+xw,
						   -(yc+yw),
						   0.0f);
				
				glVertex3f(	xc+xw,
						   -(yc+yw),
						   0.0f);
				glVertex3f(	xc,
						   -(yc+yw),
						   0.0f);
				
				glVertex3f(	xc,
						   -(yc+yw),
						   0.0f);
				glVertex3f(	xc,
						   -yc,
						   0.0f);
			}
			glEnd();
			
			
			
		}
	}
	else
	{
		if( (video->Height() > 0) && (video->Width() > 0) )
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, cameraImageTextureID);
			
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, video->Height(), video->Width(), 0, GL_BGR, GL_UNSIGNED_BYTE, video->Data());
			glBindTexture(GL_TEXTURE_2D, cameraImageTextureID);
			glColor3f(1,1,1);
			
			glBegin(GL_QUADS);
			
			float x = 1;
			float y = 1;
			
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-x,y, 0.0f);
			glTexCoord2f(1.0f, 0.0f);glVertex3f( x, y, 0.0f);
			glTexCoord2f(1.0f, 1.0f);glVertex3f( x, -y, 0.0f);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-x, -y, 0.0f);
			
			glEnd();

		}
		else
		{
			cout<<"no video..."<<endl;
		}
		glDisable(GL_TEXTURE_2D);
	}
}
int Image_Viewer::handle(int event)
{
	switch (event)
	{
		default:
			break;
	}
	return event;
}
void Image_Viewer::addImages(JMD_Vision_Image * image, int screenNumber)
{
	if(screenNumber > numberOfScreens)
	{
		cout<<"screen number exceeds number of screens"<<endl;
	}
	imageArray[screenNumber-1] = image;
}
void Image_Viewer::addVideo(JMD_Vision_Image *videoPTR)
{
	video = videoPTR;
}
void Image_Viewer::runfunction()
{
	this->show();
	while(Fl::wait())
	{
		if(m_cb!=NULL && m_p!=NULL)
			m_cb(m_p);
	}
	return;
}
#endif