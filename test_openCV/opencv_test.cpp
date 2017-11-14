#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
 
using namespace cv;
using namespace std;
 
int main( int argc, char** argv )
{
 
       Mat image;
       String imageName( "dice.png" ); // by default
		if( argc > 1)
			{
				imageName = argv[1];
			}
       
       image = imread(imageName, CV_LOAD_IMAGE_COLOR); 
       Mat converted=imread(imageName, CV_LOAD_IMAGE_COLOR); 
 
       if(! image.data )                             
       {
              cout <<  "Could not open or find the image" << std::endl ;
              return -1;
       }
 
       // Create a new matrix to hold the gray image
       
 
       // convert RGB image to gray
       //cvtColor(image, gray, CV_BGR2GRAY);
 
       namedWindow( "Display window", CV_WINDOW_AUTOSIZE );  
       imshow( "Display window", image );                 
 
		//namedWindow( "Result window", CV_WINDOW_AUTOSIZE );   
		//     imshow( "Result window", gray );
       
		//cout << " BLUE "; // prints Output sentence on screen
		//cout << (int)image.at<Vec3b>(Point(500, 280))[0];
		//cout << "  Green "; // prints Output sentence on screen
		//cout << (int) image.at<Vec3b>(Point(500, 280))[1];
		//cout << "  RED  "; // prints Output sentence on screen
		//cout << (int) image.at<Vec3b>(Point(500, 280))[2];
		
		//cout << "Width : " << image.cols << endl;
		//cout << "Height: " << image.rows << endl;
		
		for (int x=0; x<converted.cols; x++)
			{
				for (int y=0; y<converted.rows; y++)
				{
						int greenV=(int)converted.at<Vec3b>(Point(x, y))[1];
						int blueV=(int)converted.at<Vec3b>(Point(x, y))[0];
						converted.at<Vec3b>(Point(x, y))[0]=greenV;
						converted.at<Vec3b>(Point(x, y))[1]=blueV;
				}
			}
		
		namedWindow( "Result window", CV_WINDOW_AUTOSIZE );  
		imshow( "Result window", converted );    
		waitKey();                                       
		return 0;
}
