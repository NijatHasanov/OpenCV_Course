#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///contour/////

void  getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
	vector<Rect>boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>> conPoly(contours.size());
		
		string objectType;

		if (area>1000)

		{
		float peri = arcLength(contours[i], true);
		approxPolyDP(contours[i], conPoly[i], 0.02 * peri,true);
		cout <<conPoly[i].size() << endl;
		//boundRect[i] = boundingRect(conPoly[i])

		int objCor = (int)conPoly[i].size();

		if (objCor == 3){objectType ="Tri";}
		if (objCor == 4 ){objectType = "Rect";}
		if (objCor > 4 ){objectType = "Circle";}

		drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		putText(img, objectType,{boundRect[i].x, boundRect[i].y-5},FONT_HERSHEY_COMPLEX,0.75,Scalar(200,0,50),2);

		}
	}



}

/////preprocessing//////

void main() {
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	string path = "Resources/shapes.png";
	Mat img = imread(path);
	
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil,img);

    imshow("Image", img);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);

	
	waitKey(0);
	
}
