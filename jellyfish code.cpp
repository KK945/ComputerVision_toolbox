/* Name: Karthika Kamath
   College: VEERMATA JIJABAI TECHNOLOGICAL INSTITUTE (VJTI)
   Third Year Btech Electronics */

/* Problem Statement: To mark red cross at the centroid of each jellyfish in the given image */

/* sources used: http://opencv-srf.blogspot.in/p/opencv-c-tutorials.html
				 O'Reilly - Learning OpenCv book */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
     Mat img = imread("jellyfish.JPG", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "jellyfish.JPG" and store it in 'img'

     if (img.empty()) //check whether the image is loaded or not
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
          //system("pause"); //wait for a key press
          return -1;
     }

     
	 Mat imgH;
    img.convertTo(imgH, -1, 2, 0); //increase the contrast (double) so that jellyfishes gets little more distinctly separated from the background

    
    //create windows
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    namedWindow("High Contrast", CV_WINDOW_AUTOSIZE);
   
    //show the image
    imshow("Original Image", img);
    imshow("High Contrast", imgH);
    
	cvtColor(imgH, imgH, CV_BGR2GRAY); //change the color image to grayscale image
	namedWindow("GRAY", CV_WINDOW_AUTOSIZE);
	  imshow("GRAY", imgH);

    
	  Mat dst;
 
// Set threshold and maxValue
double thresh = 127;
double maxValue = 255; 
 
// Binary Threshold
threshold(imgH,dst, thresh, maxValue, THRESH_BINARY);
imshow( "threshold", dst );

vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

   findContours( dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) ); //find contours

   //erase all the small contours (dots) made of length less than 50 
   for (vector<vector<Point> >::iterator it = contours.begin(); it!=contours.end(); )
{
    if (it->size()<50)
        it=contours.erase(it);
    else
        ++it;
}

     /// Get the moments
  vector<Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { 
		 mu[i] = moments( contours[i], false );
  }

  ///  Get the mass centers
  vector<Point2f> mc( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { 
		 mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
  }



   //draw contours
   Mat drawing = Mat::zeros( dst.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       
       drawContours( drawing, contours, i, Scalar(0,255,255), 2, 8, hierarchy, 0, Point() );

	//for marking the centroid of the fishes small areas of contour needs to be neglected to avoid confusion about it being a whole fish or part of fish
       if (contourArea(contours[i])>50)
	   {
	   
	   //red cross made at the centroid
	   line( drawing,
        Point( mc[i].x -3, mc[i].y +3),
        Point(mc[i].x +3, mc[i].y - 3),
       Scalar( 0, 0, 255 ),
        2,
        8 );
line( drawing,
        Point( mc[i].x +3, mc[i].y +3),
        Point(mc[i].x - 3, mc[i].y-3),
       Scalar( 0, 0, 255 ),
        2,
        8 );
	   }
  }

  /// Show in a window
  namedWindow( "Detected", WINDOW_AUTOSIZE );
  imshow( "Detected", drawing );
  

     waitKey(0); //wait infinite time for a keypress

     destroyWindow("Original Image"); //destroy the windows
	 destroyWindow("High Contrast");
	 destroyWindow("GRAY");
	 destroyWindow("Detected");


     return 0;
}

//problem is faced where two or more jellyfishes are overlapped so they are considered as one big area and thus marks only one centroid
