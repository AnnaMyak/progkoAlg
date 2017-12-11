#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <stdio.h> 
#include <cv.h>
#include <sys/time.h>
#include <mpi.h>
#include <stdio.h>
#include <time.h>


using namespace cv;
using namespace std;



	static int numprocs;
	
	
	static double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

	
	
	
	int main(int argc, char **argv) {
	//Variablendeklaration und Test der Eingabe
	//Bildeingabe  wird ueber Konsole realisiert
	char* imageName = argv[1];
	Mat image;
	Mat result_image;
	int greenV, blueV;
	double startwtime = 0.0, endwtime;
	
	int my_rank;
	
	
	// Initialisierung des MPI-Subsystems
	MPI_Status status;
	MPI_Init (&argc, &argv);
	// Bekomme die Groesse des Communicators MPI_COMM_WORLD
    // Bekomme, wie viel Prozessen werden innerhalb der laufenden Ausfuerung erzeugt
	MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
	
	startwtime = MPI_Wtime();
	//Oeffne und lade das Eingangsbild
	image = imread( imageName, 1 );
	
	startwtime = MPI_Wtime();
	
	if( argc != 2 || !image.data )
		{
			//Fehlermeldung und Abbruch der Ausfuehrung des Programm durch fehlende Eingabe
			printf( " Sie haben kein Bild geladen \n " );
			return -1;
		}
		
		result_image=imread(imageName, CV_LOAD_IMAGE_COLOR);
	
		
	for (int x=0; x<result_image.cols; x++)
			{
				for (int y=0; y<result_image.rows; y++)
				{	
		
					if (my_rank==0)
						{
							blueV=(int)result_image.at<Vec3b>(Point(x, y))[1];
							MPI_Send(&blueV, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		
						}
		
					if (my_rank==1)
						{
							greenV=(int)result_image.at<Vec3b>(Point(x, y))[0];
							MPI_Send(&greenV, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
		
						}
		
					if (my_rank==2)
						{
							
							MPI_Recv(&blueV, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
							MPI_STATUS_IGNORE);
							result_image.at<Vec3b>(Point(x, y))[0]=blueV;
						}
		
					if (my_rank==3)
						{
							
							MPI_Recv(&greenV, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
							MPI_STATUS_IGNORE);
							result_image.at<Vec3b>(Point(x, y))[1]=greenV;
						}		
		
		}
	}
		
    
	
	
	
	imwrite( "Result_Image.jpg", result_image );
	if (my_rank==0){
		endwtime = MPI_Wtime();
		printf("wall clock time =%f\n", endwtime-startwtime);
		}
	
	MPI_Finalize ();
	
	
	
	return 0;
}
