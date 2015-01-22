/*
 //====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2014
 ==========================
 JMD_Vision_Image: Version 1.0
 ==========================
 
 ================================================================
 JMD_Vision_Image.cpp
 An image class that can hold char,short,int,float,or double data
 ================================================================
 
 //====================================================================//
 */





//====================================================================//
//====================================================================//
//============================ Preamble ==============================//
//====================================================================//
//====================================================================//


//---------------------------------------------------------------//
//------------------------- Includes ----------------------------//
//---------------------------------------------------------------//

#include "JMD_Vision_Image.hpp"

//---------------------------------------------------------------//
//------------------------ end Includes -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//----------------------- Namespaces ----------------------------//
//---------------------------------------------------------------//

//namespaces

//---------------------------------------------------------------//
//---------------------- end Namespaces -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------------- Globals -----------------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------------ end Globals --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------- Function Prototypes -----------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------ end Function Prototypes --------------------//
//---------------------------------------------------------------//

//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//





//====================================================================//
//====================================================================//
//================= JMD Vision Image Implementation ==================//
//====================================================================//
//====================================================================//

//---------------------------------------------------------------//
//-------------------------- Private ----------------------------//
//---------------------------------------------------------------//


/*----- Private Init -----*/
void JMD::JMD_Vision_Image::Private_Init(Vision_Image_Type image_type_param, unsigned int pixel_size_param)
{
	//flags
	isHeapMemory = false;
	
	//stats
	myType      = image_type_param;
	myPixelSize = pixel_size_param;
	myDataSize  = myWidth*myHeight*myChannels*myPixelSize;
}
/*--- end Private Init ---*/

//---------------------------------------------------------------//
//------------------------ end Private --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//-------------------------- Public -----------------------------//
//---------------------------------------------------------------//

/*--------------- Constructors ---------------*/
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param)
{
	Private_Init();
}
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, unsigned char *data_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param), myUCharImage(data_param) 
{
	Private_Init(IMAGE_UCHAR, sizeof(unsigned char) );
}
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, short *data_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param), myShortImage(data_param) 
{
	Private_Init(IMAGE_SHORT, sizeof(short) );
}
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, int *data_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param), myIntImage(data_param) 
{
	Private_Init(IMAGE_INT, sizeof(int) );
}
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, float *data_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param), myFloatImage(data_param) 
{
	Private_Init(IMAGE_FLOAT, sizeof(float) );
}
JMD::JMD_Vision_Image::JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, double *data_param) :
myWidth(width_param), myHeight(height_param), myChannels(channels_param), myDoubleImage(data_param) 
{
	Private_Init(IMAGE_DOUBLE, sizeof(double) );
}
/*------------- End Constructors -------------*/

	
	
/*--------------- Destructors ---------------*/
JMD::JMD_Vision_Image::~JMD_Vision_Image() 
{
	//free memory
	if (isHeapMemory)
	{
		switch(myType)
		{
			case IMAGE_UCHAR:  if(myUCharImage)  { delete [] myUCharImage;  myUCharImage  = NULL; }
			case IMAGE_SHORT:  if(myShortImage)  { delete [] myShortImage;  myShortImage  = NULL; }
			case IMAGE_INT:    if(myIntImage)    { delete [] myIntImage;    myIntImage    = NULL; }
			case IMAGE_FLOAT:  if(myFloatImage)  { delete [] myFloatImage;  myFloatImage  = NULL; }
			case IMAGE_DOUBLE: if(myDoubleImage) { delete [] myDoubleImage; myDoubleImage = NULL; }
		}
	}
}
/*------------- End Destructors -------------*/

    
 
/*--------------- Utility ---------------*/
    
/*----- Create -----*/
void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, Vision_Image_Type image_type_param)
{
	//set params
	myWidth    = width_param;
	myHeight   = height_param;
	myChannels = channels_param;
	
	//free old memory
	if (isHeapMemory)
	{
		switch(myType)
		{
			case IMAGE_UCHAR:  if(myUCharImage)  { delete [] myUCharImage;  myUCharImage  = NULL; }
			case IMAGE_SHORT:  if(myShortImage)  { delete [] myShortImage;  myShortImage  = NULL; }
			case IMAGE_INT:    if(myIntImage)    { delete [] myIntImage;    myIntImage    = NULL; }
			case IMAGE_FLOAT:  if(myFloatImage)  { delete [] myFloatImage;  myFloatImage  = NULL; }
			case IMAGE_DOUBLE: if(myDoubleImage) { delete [] myDoubleImage; myDoubleImage = NULL; }
		}
	}
	
	//create memory
	myType = image_type_param;
	switch(myType)
	{
		case IMAGE_UCHAR:  myUCharImage  = new unsigned char[myWidth*myHeight*myChannels]; myPixelSize = sizeof(unsigned char); break;
		case IMAGE_SHORT:  myShortImage  = new short[myWidth*myHeight*myChannels];         myPixelSize = sizeof(short);         break;
		case IMAGE_INT:    myIntImage    = new int[myWidth*myHeight*myChannels];           myPixelSize = sizeof(int);           break;
		case IMAGE_FLOAT:  myFloatImage  = new float[myWidth*myHeight*myChannels];         myPixelSize = sizeof(float);         break;
		case IMAGE_DOUBLE: myDoubleImage = new double[myWidth*myHeight*myChannels];        myPixelSize = sizeof(double);        break;
		
		default: 
			myType = IMAGE_UCHAR;
			myUCharImage = new unsigned char[myWidth*myHeight*myChannels];
	}
	
	//data size
	myDataSize = myWidth*myHeight*myChannels*myPixelSize;
	
	//turn on heap memory flag
	isHeapMemory = true;
}

void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, unsigned char *data_param) 
{
	//create image
	Create( height_param, width_param, channels_param, IMAGE_UCHAR);
	
	//memcpy
	if (data_param) { memcpy(myUCharImage,data_param,myWidth*myHeight*myChannels*myPixelSize); }
}
void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, short *data_param) 
{
	//create image
	Create( height_param, width_param, channels_param, IMAGE_SHORT);
	
	//memcpy
	if (data_param) { memcpy(myShortImage,data_param,myWidth*myHeight*myChannels*myPixelSize); }
}
void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, int *data_param) 
{
	//create image
	Create( height_param, width_param, channels_param, IMAGE_INT);
	
	//memcpy
	if (data_param) { memcpy(myIntImage,data_param,myWidth*myHeight*myChannels*myPixelSize); }
}
void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, float *data_param) 
{
	//create image
	Create( height_param, width_param, channels_param, IMAGE_FLOAT);
	
	//memcpy
	if (data_param) { memcpy(myFloatImage,data_param,myWidth*myHeight*myChannels*myPixelSize); }
}
void JMD::JMD_Vision_Image::Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, double *data_param) 
{
	//create image
	Create( height_param, width_param, channels_param, IMAGE_DOUBLE);
	
	//memcpy
	if (data_param) { memcpy(myDoubleImage,data_param,myWidth*myHeight*myChannels*myPixelSize); }
}
/*--- End Create ---*/
    
/*----- Color Space -----*/
/*--- End Color Space ---*/

/*--------------- Utility ---------------*/



/*--------------- Setters/Getters ---------------*/
    
/*----- Data -----*/
void* JMD::JMD_Vision_Image::Data(void *data_param)
{
	switch(myType)
	{
		case IMAGE_UCHAR:  
			if (data_param) { data_param = myUCharImage; } 
			return myUCharImage;
			break;
		case IMAGE_SHORT:  
			if (data_param) { data_param = myShortImage; } 
			return myShortImage;
			break;
		case IMAGE_INT:    
			if (data_param) { data_param = myIntImage; } 
			return myIntImage;
			break;
		case IMAGE_FLOAT:  
			if (data_param) { data_param = myFloatImage; } 
			return myFloatImage;
			break;
		case IMAGE_DOUBLE: 
			if (data_param) { data_param = myDoubleImage; } 
			return myDoubleImage;
			break;
		
		default: if (data_param) { data_param = NULL; } break;
	}
	
	return NULL;
}
/*--- End Data ---*/

/*----- DataSize -----*/
unsigned int JMD::JMD_Vision_Image::DataSize(unsigned int *data_size_param)
{
	if( data_size_param ) { *data_size_param = myDataSize; }
	return myDataSize;
}
/*--- End DataSize ---*/
    
/*----- Width -----*/
unsigned int JMD::JMD_Vision_Image::Width(unsigned int *width_param)
{
    if( width_param ) { *width_param = myWidth; }
	return myWidth;
}
/*--- End Width ---*/
    
/*----- Height -----*/
unsigned int JMD::JMD_Vision_Image::Height(unsigned int *height_param)
{
	if( height_param ) { *height_param = myHeight; }
	return myHeight;
}
/*--- End Height ---*/
    
/*----- Channels -----*/
unsigned int JMD::JMD_Vision_Image::Channels(unsigned int *channels_param)
{
	if( channels_param ) { *channels_param = myChannels; }
	return myChannels;
}
/*--- End Channels ---*/

/*----- Stride -----*/
unsigned int JMD::JMD_Vision_Image::Stride(unsigned int *stride_param)
{
	if( stride_param ) { *stride_param = myStride; }
	return myStride;
}
/*--- End Stride ---*/
        
/*----- PixelSize -----*/
unsigned int JMD::JMD_Vision_Image::PixelSize(unsigned int *pixel_size_param)
{
	if( pixel_size_param ) { *pixel_size_param = myPixelSize; }
	return myPixelSize;
}
/*--- End PixelSize ---*/
    
/*------------ End Setters/Getters ------------*/



/*--------------- Operator Overloads ---------------*/
    
/*---------- Operator + ----------*/
/*template <class T> JMD_Vision_Image<T> JMD::JMD_Vision_Image<T>::operator+(const JMD_Vision_Image<T>& image_param)
{
	
}*/
/*-------- End Operator + --------*/
    
/*---------- Operator - ----------*/
/*template <class T> JMD_Vision_Image<T> JMD::JMD_Vision_Image<T>::operator-(const JMD_Vision_Image<T>& image_param)
{
		
}*/
/*-------- End Operator - --------*/
       
/*---------- Operator = ----------*/
/*template <class T> JMD_Vision_Image<T> JMD::JMD_Vision_Image<T>::operator=(const JMD_Vision_Image<T>& image_param)
{
		
}*/
/*-------- End Operator = --------*/
        
/*---------- Operator * ----------*/
/*template <class T> JMD_Vision_Image<T> JMD::JMD_Vision_Image<T>::operator*(const JMD_Vision_Image<T>& image_param)
{
		
}*/
/*-------- End Operator * --------*/
        
/*---------- Operator () ----------*/
/*template <class T> void JMD::JMD_Vision_Image<T>::operator()(const unsigned int x_param, const unsigned int y_param)
{
		
}*/
/*-------- End Operator () --------*/
    
/*---------- Operator << ----------*/
ostream& JMD::operator << (ostream &os, const JMD::JMD_Vision_Image &image_param)
{
	//variables
	unsigned char *uchar_ptr;
	short *short_ptr;
	int *int_ptr;
	float *float_ptr;
	double *double_ptr;
	
	/*----- Output Stream -----*/
	switch(image_param.myType)
	{
		/*--- UCHAR ---*/
		case JMD::JMD_Vision_Image::IMAGE_UCHAR:  
			uchar_ptr = image_param.myUCharImage;
			for(int i=0; i < image_param.myChannels; i++)
			{
				os << "(:,:," << i << ")" << std::endl;
				for(int j=0; j < image_param.myHeight; j++) 
				{ 
					os << " "; 
					for(int k=0; k < image_param.myWidth; k++) 
					{ 
						os << (int)uchar_ptr[j*image_param.myWidth + k] << " "; 
					} 
					os << std::endl; 
				}
			}
			break;
		/*- End UCHAR -*/
		
		/*--- SHORT ---*/
		case JMD::JMD_Vision_Image::IMAGE_SHORT:  
			short_ptr = image_param.myShortImage;
			for(int i=0; i < image_param.myChannels; i++)
			{
				os << "(:,:," << i << ")" << std::endl;
				for(int j=0; j < image_param.myHeight; j++) 
				{ 
					os << " "; 
					for(int k=0; k < image_param.myWidth; k++) 
					{ 
						os << short_ptr[j*image_param.myWidth + k] << " "; 
					} 
					os << std::endl; 
				}
			}
			break;
		/*- End SHORT -*/
		
		/*--- INT ---*/
		case JMD::JMD_Vision_Image::IMAGE_INT:    
			int_ptr = image_param.myIntImage;
			for(int i=0; i < image_param.myChannels; i++)
			{
				os << "(:,:," << i << ")" << std::endl;
				for(int j=0; j < image_param.myHeight; j++) 
				{ 
					os << " "; 
					for(int k=0; k < image_param.myWidth; k++) 
					{ 
						os << int_ptr[j*image_param.myWidth + k] << " "; 
					} 
					os << std::endl; 
				}
			}
			break;
		/*- End INT -*/
		
		/*--- FLOAT ---*/
		case JMD::JMD_Vision_Image::IMAGE_FLOAT:  
			float_ptr = image_param.myFloatImage;
			for(int i=0; i < image_param.myChannels; i++)
			{
				os << "(:,:," << i << ")" << std::endl;
				for(int j=0; j < image_param.myHeight; j++) 
				{ 
					os << " "; 
					for(int k=0; k < image_param.myWidth; k++) 
					{ 
						os << float_ptr[j*image_param.myWidth + k] << " "; 
					} 
					os << std::endl; 
				}
			}
			break;
		/*- End FLOAT -*/
		
		/*--- DOUBLE ---*/
		case JMD::JMD_Vision_Image::IMAGE_DOUBLE: 
			double_ptr = image_param.myDoubleImage;
			for(int i=0; i < image_param.myChannels; i++)
			{
				os << "(:,:," << i << ")" << std::endl;
				for(int j=0; j < image_param.myHeight; j++) 
				{ 
					os << " "; 
					for(int k=0; k < image_param.myWidth; k++) 
					{ 
						os << double_ptr[j*image_param.myWidth + k] << " "; 
					} 
					os << std::endl; 
				}
			}
			break;
		/*- End DOUBLE -*/
		
		default: return os;
	}
	/*--- End Output Stream ---*/
	
	//return
	return os;
}
/*-------- End Operator << --------*/

/*--------------- Operator Overloads ---------------*/


//---------------------------------------------------------------//
//-------------------------- Public -----------------------------//
//---------------------------------------------------------------//


//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
