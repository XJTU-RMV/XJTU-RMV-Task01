#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() 
{
    string path="/home/mu/opencv_project/resources/test_image.png";
    Mat img=imread(path);
    namedWindow("img",WINDOW_AUTOSIZE);
    imshow("img",img);
    waitKey(0);     //import the photo
    Mat imgGray,imgHSV,imgBlur,imgBlur2;
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    cvtColor(img,imgHSV,COLOR_BGR2HSV);
    blur (img,imgBlur,Size(3,3)); //均值滤波
    GaussianBlur(img,imgBlur2,Size(5,5),1.5);//高斯滤波
    //imshow("imgBlur",imgBlur);
   // imshow("imgHSV",imgHSV);
    

    ////////////////////////////
    Mat mask;
    Scalar lower(129,71,172);
    Scalar upper(74,0,168);
    inRange(imgHSV,Scalar(0,120,60),Scalar(180,255,255),mask);
    Mat redRegion,redCanny;
    img.copyTo(redRegion,mask);
    imshow("redRegion",redRegion);
    
    vector<vector<Point>>contours;
    vector<Vec4i>hieraechy;
    findContours(mask,contours,hieraechy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    Mat redContours=img.clone();
    drawContours(redContours,contours,-1,Scalar(0,255,0),4);
    imshow("redContours",redContours);
    waitKey(0);
    Mat redBbox=img.clone();
    for (size_t i=0;i<contours.size();i++)
     { 
         int area=contourArea(contours[i]);
        cout<<area<<endl;
        Rect bbox=boundingRect(contours[i]);
        rectangle(redBbox,bbox,Scalar(0,0,255),2);
     }
     imshow("redBbox",redBbox);
     waitKey(0);

     /////////////////////////////

     Mat thresh,highLight,mask2,hLGray,bin;
     Scalar lower2(0,0,200);
     Scalar upper2(180,225,225);
     inRange(imgHSV,lower2,upper2,mask2);
     img.copyTo(highLight,mask2);  
     threshold(highLight,thresh,0,255,THRESH_BINARY);
     cvtColor(highLight,hLGray,COLOR_BGR2GRAY);
     
     imshow("highLight",highLight);
     imshow("thresh",thresh);
     imshow("hLGray",hLGray);
     
     waitKey(0);
     Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3));
     Mat hLDil,hLEro;
     dilate(highLight,hLDil,kernel);
     erode(highLight,hLEro,kernel);
     Point seedPoint(highLight.cols /2,highLight.rows /2);
     bin=img.clone();
     Mat mask3(img.rows +2,img.cols +2,CV_8UC1,Scalar(0));
     floodFill(bin,mask3,seedPoint,Scalar(0,0,255));
     imshow("man",bin);
     imshow("dil",hLDil);
     imshow("ero",hLEro);
     waitKey(0);

     //////////////////////////
     
     Mat imgCrop,imgWarp;
     Rect roi(200,200,img.cols /4,img.rows /4);
     imgCrop =img (roi);
     double angle =35.0;
     double scale=1.0;
     Mat rotMat=getRotationMatrix2D(seedPoint,angle,scale);
     warpAffine(img,imgWarp,rotMat,img.size());
     imshow("warp",imgWarp);
     imshow("crop",imgCrop);

     ///////////////////////

     Mat img2(512,512,CV_8SC3,Scalar(255,255,255));
     circle(img2,Point(256,256),155,Scalar(0,23,43),FILLED);
     rectangle(img2,Point(130,296),Point(382,286),Scalar(0,225,0),FILLED);
     line (img2,Point(130,296),Point(382,296),Scalar(255,255,255),2);
     putText(img2,"final",Point(137,262),FONT_HERSHEY_DUPLEX,2,Scalar(0,69,255),2);
     imshow("img2",img2);
     waitKey(0);

    return 0;
}