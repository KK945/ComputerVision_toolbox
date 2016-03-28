# ComputerVision_toolbox
##To execute the code:
####Setup
1. make an opencv (2.4.9) project in visual studio c++ 2010
 
2. so open visual studio then click on file->new project-> visual c++ -> win 32 console application
 
3. give a name and loacation to the project and click ok
 
4. in the next box you see tick empty project and finish
 
5. then ctrl+shift+A and click on c++ file, name it as main.cpp and go ahead
 
6. Make sure that "Debug" is selected in the solution configuration combobox
 
7. then in the solution explorer window right click on the project name and go to its property
 
8. go to VC++ directories
 
9. Select Include Directories to add a new entry and type C:\opencv\build\include.
 
10. Click Ok to close the dialog.Back to the Property dialog, select Library Directories to add a new entry and type     C:\opencv\build\x86\vc10\lib.
 
11. Click Ok to close the dialog.
 
12. Back to the property dialog, select Linker → Input → Additional Dependencies to add new entries. On the popup dialog, type the files below

opencv_core249d.lib 

opencv_imgproc249d.lib

opencv_highgui249d.lib

opencv_ml249d.lib

opencv_video249d.lib

opencv_features2d249d.lib

opencv_calib3d249d.lib

opencv_objdetect249d.lib

13. Click Ok to close the dialog. Click Ok on the project properties dialog to save all settings.

14. Now it is ready to write and run the code using the opencv function in C++.

####Execution

1. to execute each of the program copy the code from the given source code in this repo into this created project's main.cpp separately

2. also for each of them copy the image into the desired project folder of visual studio 2010 or directly give the path of the location where image (jellyfish.jpg and OscarSelfie.jpg) is stored by replacing the image name written in the code.

ex  img = imread("jellyfish.JPG", CV_LOAD_IMAGE_UNCHANGED); here replace the jellyfish.jpg with the path similarly for the oscarselfie code

3. also for the oscarselfie problem properly replace the path for the desired haar cascade from C:\ opencv \ sources \ data folder

4. finally to start debugging press F5

5. you could use the same project to execute both the codes by first copying code of oscarselfie and performing step 26, 27, 28 and then after erasing the previous code copying the code for jellyfish and doing the same
