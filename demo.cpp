#include <imageviewer.hpp>
#include <JMD_Vision_Image.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
VideoCapture cap;
Mat * video;

void videostream(int * a)
{
	cap >>(*video);
}

//Main program
int main(int argv, char **argc) 
{
	int choose = 1;// 1 for image 2 for video
	cin>>choose;
	
	switch (choose)
	{
		case 1:
		{
			Image_Viewer myImageViewer("test", 7);
			
			Mat image;
			image = imread("../img/lenna.bmp");
			JMD::JMD_Vision_Image * a = new JMD::JMD_Vision_Image(image.cols, image.rows, image.channels(), image.data);
			
			
			d->Create(3,3,3,data);
			
			
			myImageViewer.addImages(a,3);
			myImageViewer.runfunction();
			break;
		}
		case 2:
		{
			cap.open(0);
			video = new Mat();
			cap>>(*video);
			int*ccc = new int(3);
			JMD::JMD_Vision_Image * a = new JMD::JMD_Vision_Image(video->cols, video->rows, video->channels(),video->data);
			
			Image_Viewer myImageViewer("test", 1,&videostream,ccc);
			myImageViewer.addVideo(a);
			myImageViewer.runfunction();
			break;
		}
	}
	return 0;
	
}