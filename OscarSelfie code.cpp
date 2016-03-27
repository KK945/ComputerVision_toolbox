#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat img; Mat img_gray;
int thresh = 100;
int max_thresh = 255;


/// Function header
void thresh_callback(int, void* );

int main( int, char** argv )
{
  /// Load source image and convert it to gray
  img = imread("jellyfish.JPG", CV_LOAD_IMAGE_UNCHANGED);

  /// Convert image to gray and blur it
  cvtColor( img, img_gray, COLOR_BGR2GRAY );
  blur( img_gray, img_gray, Size(3,3) );

  /// Create Window
  const char* image_window = "Image";
  namedWindow( image_window, WINDOW_AUTOSIZE );
  imshow( image_window, img );
// taskbar created to adjust threshold to detect accordingly
  createTrackbar( " Threshold:", "Image", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

void thresh_callback(int, void* )
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using Threshold
  threshold( img_gray, threshold_output, thresh, 255, THRESH_BINARY );
  /// Find contours
  findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Approximate contours to polygons + get bounding rects and circles
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

  for( size_t i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       minEnclosingCircle( contours_poly[i], center[i], radius[i] );
     }


  /// Draw polygonal contour + bonding rects + circles
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
     {
       
       drawContours( drawing, contours_poly, (int)i, Scalar(0,255,255), 1, 8, vector<Vec4i>(), 0, Point() );
       
       circle( drawing, center[i], (int)radius[i], Scalar(255, 255, 0), 2, 8, 0 );
	   Rect bounding_rect=boundingRect(contours[i]);
	   rectangle(drawing, bounding_rect,  Scalar(0,255,0),2, 8,0);
	   //Bounding Box Centroid
Point center = Point((bounding_rect.x + bounding_rect.width/2), (bounding_rect.y + bounding_rect.height/2));

// print it:
cout<<"Rectangle " <<i<< " Centroid position is at: " << center.x << " " << center.y << endl;
//mark red cross at centroid by making two intersecting lines at centroid
line( drawing,
        Point( center.x, center.y +3),
        Point(center.x, center.y - 3),
       Scalar( 0, 0, 255 ),
        2,
        8 );
line( drawing,
        Point( center.x +3, center.y),
        Point(center.x - 3, center.y),
       Scalar( 0, 0, 255 ),
        2,
        8 );
  }

  /// Show in a window
  namedWindow( "Detected", WINDOW_AUTOSIZE );
  imshow( "Detected", drawing );
} 

