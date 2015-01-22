#pragma once
#ifndef JMD_VISION_IMAGE_H_
#define JMD_VISION_IMAGE_H_

/*
 //====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2014
 ==========================
 JMD_Vision_Image: Version 1.0
 ==========================
 
 ================================================================
 JMD_Vision_Image.hpp
 An image class that can hold char,short,int,float,or double data
 ================================================================
 
 List of Functions:
 
 ----- Enumerations -----
 
 --- End Enumerations ---
 
 ----- Constructors -----
 
 --- end Constructors ---
 
 ----- Utility Methods -----
 
 --- End Utility Methods ---
 
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

//system
#include <iostream>
#include <cstring>

//---------------------------------------------------------------//
//------------------------ end Includes -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//----------------------- Namespaces ----------------------------//
//---------------------------------------------------------------//

using namespace std;
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

/*----- Forward Declerations -----*/
namespace JMD {
	class JMD_Vision_Image;
	ostream &operator << (ostream &, const JMD_Vision_Image &);
	istream &operator >> (istream &, const JMD_Vision_Image &);
}
/*--- End Forward Declerations ---*/

//---------------------------------------------------------------//
//------------------ end Function Prototypes --------------------//
//---------------------------------------------------------------//

//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//







namespace JMD {
    
    //====================================================================//
    //====================================================================//
    //=================== JMD Vision Image Definition ====================//
    //====================================================================//
    //====================================================================//
    class JMD_Vision_Image
    {
        
        /*--------------- Enumerations ---------------*/
        public:
        
        /*--- Image Type ---*/
        // Defines the type of the image
        //
        // IMAGE_UCHAR  - unsigned char
        // IMAGE_SHORT  - short
        // IMAGE_INT    - integer
        // IMAGE_FLOAT  - floating point
        // IMAGE_DOUBLE - double precision floating point
        typedef enum Vision_Image_Type { IMAGE_UCHAR = 0, IMAGE_SHORT, IMAGE_INT, IMAGE_FLOAT, IMAGE_DOUBLE } Vision_Image_Type;
        /*- End Image Type -*/
        
        /*------------- End Enumerations -------------*/
        
        //---------------------------------------------------------------//
        //------------------------- Private -----------------------------//
        //---------------------------------------------------------------//
        private:
        
        /*--------------- Variables ---------------*/
        
        //stats
        int myHeight;
        int myWidth;
        int myChannels;
        int myPixelSize;
        int myDataSize;
        int myStride;
        Vision_Image_Type myType;
        
        //flags
        bool isHeapMemory;
        
        //data
        union
        {
			unsigned char   *myUCharImage;
			short           *myShortImage;
			int             *myIntImage;
			float           *myFloatImage;
			double          *myDoubleImage;
		};
		
        /*------------- End Variables -------------*/
        
        /*--------------- Helpers ---------------*/
        
        /*----- Private Init -----*/
        // does all the initialization of private instance variables
        //
        // input:
        //    image_type_param - image type enumeration
        void Private_Init(Vision_Image_Type image_type_param = IMAGE_UCHAR, unsigned int pixel_size_param = 0);
        /*--- End Private Init ---*/
        
        /*------------- End Helpers -------------*/
        
        //---------------------------------------------------------------//
        //----------------------- end Private ---------------------------//
        //---------------------------------------------------------------//
        
        
        //---------------------------------------------------------------//
        //-------------------------- Public -----------------------------//
        //---------------------------------------------------------------//
        public:
        
		/*--------------- Constructors ---------------*/
		// Constructors for image, does not allocate memory, see create for
        // allocating memory
        //
        // input:
        //    height_param - image height
        //    width_param - image width
        //    channels_param - image channels
        //    data_param - pointer to data
        JMD_Vision_Image(unsigned int height_param = 0, unsigned int width_param = 0, unsigned int channels_param = 0);
		JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, unsigned char   *data_param);
		JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, int             *data_param);
		JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, short           *data_param);
		JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, float           *data_param);
		JMD_Vision_Image(unsigned int height_param, unsigned int width_param, unsigned int channels_param, double          *data_param);
		/*------------- end Constructors -------------*/
		
		
		/*--------------- Destructors ---------------*/
		~JMD_Vision_Image();
		/*------------- end Destructors ------------*/
		
        
        /*--------------- Utility Methods ---------------*/
        
        /*----- Create -----*/
        // Allocates memory for storing an image and sets the data if
        // provided
        //
        // input:
        //    width_param - image width
        //    height_param - image height
        //    channels_param - image channels
        //    data_param - image data
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, Vision_Image_Type image_type_param);
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, unsigned char *data_param);
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, short         *data_param);
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, int           *data_param);
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, float         *data_param);
        void Create(unsigned int height_param, unsigned int width_param, unsigned int channels_param, double        *data_param);
        /*--- End Create ---*/
        
        /*----- Deep Copy -----*/
        /*--- End Deep Copy ---*/
        
        /*----- Shallow Copy -----*/
        /*--- End Shallow Copy ---*/
        
        /*----- Color Space -----*/
        // converts an image to the specified color space
        void ColorSpace();
        /*--- End Color Space ---*/
        
        /*----- Subsample -----*/
        /*--- End Subsample ---*/
        
        /*----- Invert -----*/
        /*--- End Invert ---*/
        
        /*------------- End Utility Methods -------------*/
        
        
        /*--------------- Setters/Getters ---------------*/
        
        /*----- Pixel -----*/
        //T Pixel(unsigned int x_param, unsigned int y_param);
        //void Pixel(unsigned int x_param, unsigned int y_param, T value_param);
        /*--- End Pixel ---*/
        
        /*----- Data -----*/
        void* Data(void *image_data_param = NULL);
        /*--- End Data ---*/
        
        /*----- DataSize -----*/
        unsigned int DataSize(unsigned int *data_size_param = NULL);
        /*--- End DataSize ---*/
        
        /*----- Width -----*/
        unsigned int Width(unsigned int *width_param = NULL);
        /*--- End Width ---*/
        
        /*----- Height -----*/
        unsigned int Height(unsigned int *height_param = NULL);
        /*--- End Height ---*/
        
        /*----- Channels -----*/
        unsigned int Channels(unsigned int *channels_param = NULL);
        /*--- End Channels ---*/
        
        /*----- Stride -----*/
        unsigned int Stride(unsigned int *stride_param = NULL);
        /*--- End Stride ---*/
        
        /*----- PixelSize -----*/
        unsigned int PixelSize(unsigned int *pixel_size_param = NULL);
        /*--- End PixelSize ---*/
        /*-----myType	------*/
		Vision_Image_Type myTypes() {return myType;}
        
        /*------------- End Setters/Getters -------------*/
        
        
        /*--------------- Operator Overloads ---------------*/
        
        /*----- Operator + -----*/
        //JMD_Vision_Image<T> operator+(const JMD_Vision_Image<T>& image_param);
        /*--- End Operator + ---*/
        
        /*----- Operator - -----*/
        //JMD_Vision_Image<T> operator-(const JMD_Vision_Image<T>& image_param);
        /*--- End Operator - ---*/
        
        /*----- Operator = -----*/
        //JMD_Vision_Image<T> operator=(const JMD_Vision_Image<T>& image_param);
        /*--- End Operator = ---*/
        
        /*----- Operator * -----*/
        //JMD_Vision_Image<T> operator*(const JMD_Vision_Image<T>& image_param);
        /*--- End Operator * ---*/
        
        /*----- Operator () -----*/
        //void operator()(const unsigned int x_param, const unsigned int y_param);
        /*--- End Operator () ---*/
        
        /*----- Operator [] -----*/
        //JMD_Vision_Image<T> operator[](const JMD_Vision_Image<T>& image_param);
        /*--- End Operator [] ---*/
        
        /*----- Operator << -----*/
        friend ostream &operator << (ostream &, const JMD_Vision_Image &);
        /*--- End Operator << ---*/
        
        /*----- Operator >> -----*/
        /*--- End Operator >> ---*/
        
        /*------------- End Operator Overloads -------------*/
        
        
        //---------------------------------------------------------------//
        //------------------------ end Public ---------------------------//
        //---------------------------------------------------------------//
        
        
    };
    //====================================================================//
    //====================================================================//
    //====================================================================//
    //====================================================================//
    //====================================================================//
    
    
    
    
        
    //====================================================================//
    //====================================================================//
    //==================== JMD Vision Image Typedefs =====================//
    //====================================================================//
    //====================================================================//
    
    /*typedef JMD_Vision_Image<unsigned char>      JMD_Vision_UCharImage;
    typedef JMD_Vision_Image<unsigned short>     JMD_Vision_UShortImage;
    typedef JMD_Vision_Image<unsigned int>       JMD_Vision_UIntImage;
    typedef JMD_Vision_Image<unsigned long>      JMD_Vision_ULongImage;
    typedef JMD_Vision_Image<unsigned long long> JMD_Vision_ULongLongImage;
    
    typedef JMD_Vision_Image<char>      JMD_Vision_CharImage;
    typedef JMD_Vision_Image<short>     JMD_Vision_ShortImage;
    typedef JMD_Vision_Image<int>       JMD_Vision_IntImage;
    typedef JMD_Vision_Image<long>      JMD_Vision_LongImage;
    typedef JMD_Vision_Image<long long> JMD_Vision_LongLongImage;
    
    typedef JMD_Vision_Image<double> JMD_Vision_DoubleImage;
    typedef JMD_Vision_Image<float>  JMD_Vision_FloatImage;*/
    
    //====================================================================//
    //====================================================================//
    //==================== JMD Vision Image Typedefs =====================//
    //====================================================================//
    //====================================================================//
    
}//end namespace JMD


#endif

