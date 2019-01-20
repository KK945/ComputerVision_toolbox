/* Name: Karthika Kamath
   College: VEERMATA JIJABAI TECHNOLOGICAL INSTITUTE (VJTI)
   Third Year Btech Electronics */

/* Problem Statement: To find color of Ellen DeGeneres from the given image */

/*sources: http://opencvexamples.blogspot.com/p/learning-opencv-functions-step-by-step.html */


#include "opencv2/objdetect/objdetect.hpp" //for facial feature extraction using haarcascades
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
#include <iostream>

 
using namespace std;
using namespace cv;
 
int main( )
{
   
	Mat image;
// load image and create a window to display
    image = imread("oscarSelfie.jpg", CV_LOAD_IMAGE_COLOR);  
    namedWindow( "window1", 1 );  
	imshow( "window1", image );
 
    // Load Face cascade (.xml file)
    CascadeClassifier face_cascade, eyes_cascade;
    face_cascade.load( "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml" );
	eyes_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml" );
    

  
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY); //color to gray
    equalizeHist(grayImage, grayImage);// histogram equilisation

    // detect the faces on the image
    vector<Rect> faces;
    face_cascade.detectMultiScale(grayImage, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(90,90));

    for (int i = 0; i < faces.size(); i++)
	{
        // visualize the faces
        Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        Point pt2(faces[i].x, faces[i].y);
        rectangle(image, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8 ,0);
        // detect the eyes within the facial roi
        Rect rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
        Mat roi = grayImage(rect);
        vector<Rect> eyes;
       // in each face detect eyes
        eyes_cascade.detectMultiScale(roi, eyes, 1.1, 2,0|CV_HAAR_SCALE_IMAGE , Size(30, 30));
		
        //since at i=3 Ellen’s face is being detected as it is the 4th face detected starting from left to right

		if (i==3)
		{
        for (int j = 0; j < eyes.size(); j++)
		{
            // visualize the eyes
            Point pt1(faces[i].x + eyes[j].x + eyes[j].width, faces[i].y + eyes[j].y + eyes[j].height);
            Point pt2(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y);
            rectangle(image, pt1, pt2, cvScalar(0, 210, 255, 0), 1, 8 ,0);
			cout<<"dimensions and centroid of eye "<< j+1 << eyes[j]<<endl;
		
		//finding rgb value at the centroid of the eye	
        int b = roi.at<Vec3b>(eyes[j].x, eyes[j].y)[0];
        int g = roi.at<Vec3b>(eyes[j].x, eyes[j].y)[1];
        int r = roi.at<Vec3b>(eyes[j].x, eyes[j].y)[2];
        cout<<"rgb value of eye "<< j+1<<":" << r << " " << g << " " << b << endl ;
        
		}
    }
	}
//show it in another window     
    imshow( "Detected Face", image );
     
    waitKey(0);                   
    return 0;
}


