#ifndef Kinect_h__
#define Kinect_h__

#include <XnCppWrapper.h>

using namespace xn;

class Kinect
{
public:
	Kinect(){}
	~Kinect(){ReleseKinect();}	

	// kinect variable
	xn::Context			context;
	xn::DepthGenerator	depth_generator;
	xn::ImageGenerator	image_generator;

	xn::Recorder		recorder;
	xn::Player			player;
	XnMapOutputMode		mapMode;  

	int InitKinect(const char* filename = NULL)
	{
		XnStatus rc;
		if (rc = context.Init() != XN_STATUS_OK)
		{
			printf("Context Init error: %s\n", xnGetStatusString(rc));
			return 1;
		}

		if (filename)
		{
			if(rc = context.OpenFileRecording(filename, player) != XN_STATUS_OK)
			{
				printf("Open File Recording error: %s\n", xnGetStatusString(rc));
				return 1;
			}
		}

		if (rc = depth_generator.Create(context) != XN_STATUS_OK)
		{
			printf("Depth generator error : %s\n", xnGetStatusString(rc));
			return 1;
		}	
		if (rc = image_generator.Create(context) != XN_STATUS_OK)
		{
			printf("Image generator error : %s\n", xnGetStatusString(rc));
			return 1;
		}

		if (!filename)
		{
			mapMode.nXRes = XN_VGA_X_RES; 
			mapMode.nYRes = XN_VGA_Y_RES; 
			mapMode.nFPS = 30;

			if (depth_generator.SetMapOutputMode(mapMode) != XN_STATUS_OK)
			{
				printf("Depth SetMapOutputMode error: %s\n", xnGetStatusString(rc));
				return 1;
			}
			if (image_generator.SetMapOutputMode(mapMode) != XN_STATUS_OK)
			{
				printf("Image SetMapOutputMode error: %s\n", xnGetStatusString(rc));
				return 1;
			}		
		}
		
		printf("kinect is ready.\n");
		return 0;
	}
	
	void ReleseKinect()
	{
		if (recorder.IsValid()) recorder.Release();
		if (player.IsValid()) player.Release();

		if (depth_generator.IsValid()) depth_generator.Release();
		if (image_generator.IsValid()) image_generator.Release();
		context.Release();
	}
};


#endif // Kinect_h__