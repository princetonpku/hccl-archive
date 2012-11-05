#include "PostProcessing.h"
#include <QTimer>
#include <QFileDialog>
#include <fstream>

using namespace cv;
using namespace std;

PostProcessing::PostProcessing(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags), near_dist(600), far_dist(900), mx_dist(1000)
{
	timer = new QTimer;
	ui.setupUi(this);

	ui.graphicsView_kinect->SetParentPtr(this);
	ui.graphicsView_cut->SetParentPtr(this);

	ui.spinBox_near->setMaximum(1000);
	ui.horizontalSlider_near->setMaximum(1000);
	ui.spinBox_far->setMaximum(3000);
	ui.horizontalSlider_far->setMaximum(3000);	
	
	ui.label_rgb->setFixedSize(320, 240);
	
	connect(ui.pushButton_play, SIGNAL(clicked()), this, SLOT(Play()));
	connect(ui.pushButton_load, SIGNAL(clicked()), this, SLOT(Load()));
	connect(ui.pushButton_cut1, SIGNAL(clicked()), this, SLOT(Cut1()));
	connect(ui.pushButton_cut2, SIGNAL(clicked()), this, SLOT(Cut2()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback(int)));
	connect(ui.horizontalSlider_near, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback_near(int)));
	connect(ui.horizontalSlider_far, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback_far(int)));
	connect(timer, SIGNAL(timeout()), this, SLOT(TimerCallback()));

	ui.horizontalSlider_near->setValue(near_dist);
	ui.horizontalSlider_far->setValue(far_dist);

	Load("sample1.oni");
	int f = 40;
	ui.horizontalSlider->setValue(f);
	SliderCallback(f);
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::TimerCallback()
{	
	if (ui.horizontalSlider->value() == ui.horizontalSlider->maximum())
	{
		ui.horizontalSlider->setValue(0);
		SliderCallback(0);
		timer->stop();
	}
	else
	{
		ui.horizontalSlider->setValue(ui.horizontalSlider->value()+1);		
	};
}

void PostProcessing::SliderCallback( int f )
{
	if (kinect.player.IsValid())
	{
		kinect.context.WaitAndUpdateAll();
		kinect.player.SeekToFrame(kinect.depth_generator.GetName(), f, XN_PLAYER_SEEK_SET);

		// color image
		const XnRGB24Pixel* pColorMap = kinect.image_generator.GetRGB24ImageMap();
		colorMap = Mat(y_res, x_res, CV_8UC3, (uchar*)pColorMap);
		ui.label_rgb->UpdatePixmap(QPixmap::fromImage(QImage((uchar*)pColorMap, x_res, y_res ,QImage::Format_RGB888).scaled(ui.label_rgb->size())));

		// depth image	
		const XnDepthPixel* pDepthMap = kinect.depth_generator.GetDepthMap();
		
		depthMap = Mat(XN_VGA_Y_RES, XN_VGA_X_RES, CV_16UC1, (unsigned short*)pDepthMap);
		double mx;
		minMaxLoc(depthMap, NULL, &mx);

		Mat depth_display;
		depthMap.convertTo(depth_display, CV_8U, 255/mx);
		cvtColor(depth_display, depth_display, CV_GRAY2BGR);
		ui.label_depth->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, x_res, y_res ,QImage::Format_RGB888).scaled(ui.label_depth->size())));

		pt_projected.clear();
		pt_color.clear();

		pt_projected.reserve(total);		
		pt_color.reserve(total);

		for (int i = 0; i<total; ++i)
		{
			int indx_a = i+1;		
			int indx_d = i+x_res;
			int indx_da = indx_d+1;

 			if (pDepthMap[i]>near_dist && pDepthMap[i]<far_dist)
			{
				int x = i%x_res;				
				int y = i/x_res;

				XnPoint3D tem;	

				// save position data
				tem.X = x; tem.Y = y; tem.Z = pDepthMap[i];
				pt_projected.push_back(tem);

				// save color data
				tem.X = pColorMap[i].nRed; tem.Y = pColorMap[i].nGreen; tem.Z = pColorMap[i].nBlue;
				pt_color.push_back(tem);
			}
		}

		pt_real.resize(pt_projected.size());
		kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected.size(), pt_projected.data(), pt_real.data());

		ui.graphicsView_kinect->updateGL();
	}
}

void PostProcessing::Load()
{
	// get file name
	QString file = QFileDialog::getOpenFileName(this,"Select one or more files to open", "", "kinect (*.oni)");
	if(file.isEmpty()) return;

	Load(file.toStdString().c_str());

	if (ui.horizontalSlider->value()!=0) ui.horizontalSlider->setValue(0);
	else SliderCallback(0);
}

void PostProcessing::Load( const char* filename )
{
	// init kinect form file
	if (kinect.InitKinect(filename))
	{
		printf("Load failed!\n");
	}

	// get max fame
	unsigned mx_frame;
	kinect.player.GetNumFrames(kinect.depth_generator.GetName(), mx_frame);
	UpdateMaxFrame(mx_frame);

	// init 3d data
	XnMapOutputMode outputmode;
	kinect.depth_generator.GetMapOutputMode(outputmode);
	x_res = outputmode.nXRes;
	y_res = outputmode.nYRes;
	total = x_res*y_res;

	ui.graphicsView_kinect->updateGL();
	ui.graphicsView_kinect->z_translate = -(near_dist+far_dist)*0.5;
	ui.graphicsView_kinect->setSceneRadius((far_dist-near_dist)*0.6);
	ui.graphicsView_kinect->showEntireScene();
}

void PostProcessing::Play()
{
	if (timer->isActive())
	{
		timer->stop();
	} 
	else
	{
		timer->start(30);
	}
}

void PostProcessing::UpdateMaxFrame( int mx )
{	
	ui.spinBox_maxframe->setMaximum(mx);
	ui.spinBox_curframe->setMaximum(mx);
	ui.horizontalSlider->setMaximum(mx);
	ui.spinBox_maxframe->setValue(mx);
}

void PostProcessing::Cut1()
{
	Cut(0);
	SaveMesh("cut1.off", pt_real2[0], tri_indx[0]);
	SaveIndx("indx1.txt", vertex_indx[0]);
	cout<< "template num vertices : " << pt_real2[0].size() << endl;
	cout<< "template num faces : " << tri_indx[0].size() << endl;
}

void PostProcessing::Cut2()
{
// 	Cut(1);
// 	SaveMesh("cut2.off", pt_real2[1], tri_indx[1]);
// 	cout<< "target num vertices : " << pt_real2[1].size() << endl;
// 	cout<< "target num faces : " << tri_indx[1].size() << endl;

	Cut(1);
	SaveMesh("cut2.off", pt_real2[1], tri_indx[1]);
	SaveIndx("indx2.txt", vertex_indx[1]);
	cout<< "target num vertices : " << pt_real2[1].size() << endl;
	cout<< "target num faces : " << tri_indx[1].size() << endl;
}

void PostProcessing::Cut( int indx )
{
	if(ui.label_rgb->mouse_press.x()<0 || ui.label_rgb->mouse_press.y()<0) return;

	// define ROI of kinect images
	Point p1(ui.label_rgb->mouse_press.x(), ui.label_rgb->mouse_press.y());
	Point p2(ui.label_rgb->mouse_relaese.x(), ui.label_rgb->mouse_relaese.y());
	roi = Rect(p1*2, p2*2);

	ui.spinBox_x->setValue(roi.x);
	ui.spinBox_y->setValue(roi.y);
	ui.spinBox_w->setValue(roi.width);
	ui.spinBox_h->setValue(roi.height);

	// get ROI of kinect images
	colorMap_cut = Mat(colorMap, roi).clone();
	depthMap_cut = Mat(depthMap, roi).clone();

	Mat cut1, cut2, msk1, msk2, msk3, depthMap_result;

	cut1 = depthMap_cut > near_dist;
	cut2 = depthMap_cut < far_dist;	

	bitwise_and(cut1, cut2, msk1);
	bitwise_not(msk1, msk2);

	msk1.convertTo(msk1, CV_16UC1, 1.0/255.0);
	msk2.convertTo(msk3, CV_16UC1, mx_dist/255.0);

	multiply(depthMap_cut, msk1, depthMap_result);
	add(depthMap_result, msk3, depthMap_result, msk2);

	Mat depth_display, wsl_depthmap;
	depthMap_result.convertTo(depthMap_result, CV_64FC1);	

	depthMap_result.convertTo(depth_display, CV_8U, 255.0/mx_dist);
	cvtColor(depth_display, depth_display, CV_GRAY2BGR);

	if (indx)
	{
		imshow("origin", depth_display);
		WSLApproximation(depthMap_result, wsl_depthmap, pd_Xmap, pd_Ymap);
		wsl_depthmap.convertTo(depth_display, CV_8U, 255.0/mx_dist);
		cvtColor(depth_display, depth_display, CV_GRAY2BGR);
		imshow("approximation", depth_display);
	
		Mat error;
		cv::absdiff(depthMap_result, wsl_depthmap, error);
		double minval, mxval;
		minMaxLoc(error, &minval, &mxval);
		cout << "min val : " << minval << endl;
		cout << "max val : " << mxval << endl;

		cout << Mat(wsl_depthmap, Rect(0,0,5,5)) << endl;

		depthMap_result = wsl_depthmap;
	}

	// draw ROI depth image
	ui.label_cut->setFixedSize(roi.width, roi.height);
	ui.label_cut->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, depth_display.cols, depth_display.rows, QImage::Format_RGB888)).scaled(ui.label_cut->size()));

	GetMeshData(depthMap_result, pt_projected2[indx], pt_real2[indx], tri_indx[indx]);

	// save indx
	vertex_indx[indx].resize(pt_projected2[indx].size());
	for (int i = 0; i<pt_projected2[indx].size(); ++i)
	{
		vertex_indx[indx][i].x = pt_projected2[indx][i].X;
		vertex_indx[indx][i].y = pt_projected2[indx][i].Y;
	}

	if (indx)
	{
		SaveDepthMap("target_dmap.txt", depthMap_result);
		SaveMat("pdx.txt", pd_Xmap);
		SaveMat("pdy.txt", pd_Ymap);
		
// 		ofstream fout("check_map.txt");		
// 		for (int i = 0; i<checkmap.rows; ++i)
// 		{
// 			for (int j = 0; j<checkmap.cols; ++j)
// 			{
// 				fout<< int(checkmap.at<uchar>(i, j)) << " ";
// 			}
// 			fout << endl;
// 		}
	}

	int iter = 6;
	for (int i = 0; i<iter; ++i) Smooth(indx);

	UpdateFacetNormal(indx);
	UpdateVertexNormal(indx);

 	ui.graphicsView_cut->z_translate = -(near_dist+mx_dist)*0.5;
	ui.graphicsView_cut->setSceneRadius((mx_dist-near_dist)*0.6);
	ui.graphicsView_cut->showEntireScene();
	ui.graphicsView_cut->updateGL();
}

void PostProcessing::Cut_3( int indx )
{
	if(ui.label_rgb->mouse_press.x()<0 || ui.label_rgb->mouse_press.y()<0) return;

	// define ROI of kinect images
	Point p1(ui.label_rgb->mouse_press.x(), ui.label_rgb->mouse_press.y());
	Point p2(ui.label_rgb->mouse_relaese.x(), ui.label_rgb->mouse_relaese.y());
	roi = Rect(p1*2, p2*2);

	ui.spinBox_x->setValue(roi.x);
	ui.spinBox_y->setValue(roi.y);
	ui.spinBox_w->setValue(roi.width);
	ui.spinBox_h->setValue(roi.height);

	// get ROI of kinect images
	colorMap_cut = Mat(colorMap, roi).clone();
	depthMap_cut = Mat(depthMap, roi).clone();

	Mat cut1, cut2, msk1, msk2, msk3, depthMap_result;

	cut1 = depthMap_cut > near_dist;
	cut2 = depthMap_cut < far_dist;	

	bitwise_and(cut1, cut2, msk1);
	bitwise_not(msk1, msk2);

	msk1.convertTo(msk1, CV_16UC1, 1.0/255.0);
	msk2.convertTo(msk3, CV_16UC1, mx_dist/255.0);

	multiply(depthMap_cut, msk1, depthMap_result);
	add(depthMap_result, msk3, depthMap_result, msk2);

	Mat depth_display;
	depthMap_result.convertTo(depth_display, CV_8U, 255.0/mx_dist);
	cvtColor(depth_display, depth_display, CV_GRAY2BGR);

	// draw ROI depth image
	ui.label_cut->setFixedSize(roi.width, roi.height);
	ui.label_cut->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, depth_display.cols, depth_display.rows, QImage::Format_RGB888)));

	// initialize data vector
	int t = roi.width*roi.height;
	pt_projected2[indx].clear();
	pt_projected2[indx].reserve(t);
	pt_color2[indx].clear();
	pt_color2[indx].reserve(t);
	tri_indx[indx].clear();
	tri_indx[indx].reserve(t*2);

	int nx = 0, ny = 0;
	XnPoint3D tem;
	double up, down, left, right;
	double thr = 5;
	std::vector<int> tri(3,0);

	// get data
	for (int i = 0; i<roi.height; ++i)
	for (int j = 0; j<roi.width; ++j)
	{
		nx = j+roi.x;
		ny = i+roi.y;

		// get position data		
		if (i>0 && j>0)
		{
			tem.X = nx;
			tem.Y = ny;
			tem.Z = depthMap_result.at<short>(i,j);		
			pt_projected2[indx].push_back(tem);

			tem.Y -= 1; tem.Z = depthMap_result.at<short>(i-1,j);
			pt_projected2[indx].push_back(tem);

			tem.X -= 1; tem.Y += 1; tem.Z = depthMap_result.at<short>(i,j-1);
			pt_projected2[indx].push_back(tem);

			tri[0] = i*roi.width+j;
			tri[2] = (i-1)*roi.width+j;
			tri[1] = i*roi.width+(j-1);
			tri_indx[indx].push_back(tri);
		}

		if (i<roi.height-1 && j<roi.width-1)
		{
			tem.X = nx;
			tem.Y = ny;
			tem.Z = depthMap_result.at<short>(i,j);		
			pt_projected2[indx].push_back(tem);

			tem.Y += 1; tem.Z = depthMap_result.at<short>(i+1,j);
			pt_projected2[indx].push_back(tem);

			tem.X += 1; tem.Y -= 1; tem.Z = depthMap_result.at<short>(i,j+1);
			pt_projected2[indx].push_back(tem);

			tri[0] = i*roi.width+j;
			tri[2] = (i+1)*roi.width+j;
			tri[1] = i*roi.width+(j+1);
			tri_indx[indx].push_back(tri);
		}
	}

	// sorting projected points and face indx
	std::sort(pt_projected2[indx].begin(), pt_projected2[indx].end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
		if(ei.Y < ej.Y) return true;
		else if(ei.Y > ej.Y) return false;
		else return (ei.X < ej.X);
	});
	std::vector<XnPoint3D>::iterator it = std::unique(pt_projected2[indx].begin(), pt_projected2[indx].end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
		return (ei.X == ej.X && ei.Y == ej.Y);
	});
	pt_projected2[indx].erase(it, pt_projected2[indx].end());


	pt_real2[indx].resize(pt_projected2[indx].size());
	kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected2[indx].size(), pt_projected2[indx].data(), pt_real2[indx].data());

	Smooth(indx);
	UpdateFacetNormal(indx);
	UpdateVertexNormal(indx);

	ui.graphicsView_cut->z_translate = -(near_dist+mx_dist)*0.5;
	ui.graphicsView_cut->setSceneRadius((mx_dist-near_dist)*0.6);
	ui.graphicsView_cut->showEntireScene();
	ui.graphicsView_cut->updateGL();
}

void PostProcessing::SliderCallback_near( int f )
{
	near_dist = f;
	SliderCallback(ui.horizontalSlider->value());
}

void PostProcessing::SliderCallback_far( int f )
{
	far_dist = f;
	SliderCallback(ui.horizontalSlider->value());
}

void PostProcessing::SaveMesh( const char* filename, const std::vector<XnPoint3D>& real, const std::vector<std::vector<int>>& tri )
{
	ofstream fout(filename);
	fout << "OFF" << endl;
	fout << real.size() << " " << tri.size() << " " << 0 << endl;
	
	for (int i = 0; i<real.size(); ++i)
	{
		fout << real[i].X << " " << real[i].Y << " " << real[i].Z << endl;
	}
	for (int i = 0; i<tri.size(); ++i)
	{
		fout << 3 << " " << tri[i][0] << " " << tri[i][1] << " " << tri[i][2] << endl;
	}
	fout.close();
}

void PostProcessing::SaveDepthMap( const char* filename, const cv::Mat& dmap )
{
	ofstream fout(filename);
	fout << roi.x<< " " << roi.y<< " " << roi.width << " " << roi.height << endl;
	for (int i = 0; i<dmap.rows; ++i)
	{
		for (int j = 0; j<dmap.cols; ++j)
		{
			fout<< dmap.at<double>(i, j) << " ";
		}
		fout << endl;
	}	
}

void PostProcessing::SaveMat( const char* filename, const cv::Mat& dmap )
{
	ofstream fout(filename);
	for (int i = 0; i<dmap.rows; ++i)
	{
		for (int j = 0; j<dmap.cols; ++j)
		{
			fout<< dmap.at<double>(i, j) << " ";
		}
		fout << endl;
	}	

}

void PostProcessing::SaveIndx( const char* filename, const std::vector<cv::Point>& v_indx )
{
	ofstream fout(filename);
	for (int i = 0; i<v_indx.size(); ++i)
	{
		fout << v_indx[i].x << " " << v_indx[i].y << endl;
	}
}

void PostProcessing::UpdateFacetNormal( int indx )
{
	cv::Vec3f pts[3];
	face_normal[indx].resize(tri_indx[indx].size());
	for (int i = 0; i<tri_indx[indx].size(); ++i)
	{				
		for (int j = 0; j<3; ++j)
		{
			int ii = tri_indx[indx][i][j];
			pts[j] = cv::Vec3f(pt_real2[indx][ii].X, pt_real2[indx][ii].Y, pt_real2[indx][ii].Z);
		}		
		face_normal[indx][i] = normalize((pts[1]-pts[0]).cross(pts[2]-pts[0]));
	}
}

void PostProcessing::UpdateVertexNormal( int indx )
{
	vertex_normal[indx].resize(pt_real2[indx].size(), Vec3f(0,0,0));
	for(int i = 0; i < tri_indx[indx].size(); i++)
	{
		int n0 = tri_indx[indx][i][0];
		int n1 = tri_indx[indx][i][1];
		int n2 = tri_indx[indx][i][2];

		vertex_normal[indx][n0] += face_normal[indx][i];
		vertex_normal[indx][n1] += face_normal[indx][i];
		vertex_normal[indx][n2] += face_normal[indx][i];
	}	
	for(int i = 0; i < vertex_normal[indx].size(); i++)
		vertex_normal[indx][i] = normalize(vertex_normal[indx][i]);

}

void PostProcessing::Smooth( int indx )
{
	std::vector<Vec3f> temp(pt_real2[indx].size(), Vec3f(0,0,0));
	std::vector<int> cnt(pt_real2[indx].size(), 0);
	
	for (int i = 0; i<tri_indx[indx].size(); ++i)
	{
		Vec3f face_center;
		int ii[3];
		for (int j = 0; j<3; ++j)
		{
			ii[j] = tri_indx[indx][i][j];
			face_center += cv::Vec3f(pt_real2[indx][ii[j]].X, pt_real2[indx][ii[j]].Y, pt_real2[indx][ii[j]].Z);
		}		
		face_center /= 3.0;
		
		for (int j = 0; j<3; ++j)
		{
			temp[ii[j]] += face_center;
			cnt[ii[j]] += 1;
		}			
	}

	for(int i = 0; i < pt_real2[indx].size(); i++)
	{
		if(cnt[i] > 0)
		{
			Vec3f dx = temp[i];
			dx /= cnt[i];
			pt_real2[indx][i].X = dx[0];
			pt_real2[indx][i].Y = dx[1];
			pt_real2[indx][i].Z = dx[2];
		}
	}
}

void PostProcessing::WSLApproximation( const cv::Mat& source, cv::Mat& result, cv::Mat& pdx, cv::Mat& pdy )
{
	// 2-D polynomial basis [1, x, y, xy, x*x, y*y]
	// Wendland function f(r) = (1+4*r/h)*(1-r/h)^4
	// h : support radius 
	int row = source.rows, col = source.cols;

	double h = 3, hh = h-1;
	auto w_fun = [h](double y1)->double
	{
		if (y1 >= h) return 0;
		double a = y1/h;
		double b = 1+4*a;
		double c = 1-a;
		return b*c*c*c*c;
	};

	Mat w_mask(h*2-1,h*2-1 , CV_64FC1);
	for (int i = 0; i<w_mask.rows; ++i)
	for (int j = 0; j<w_mask.cols; ++j)
	{
		double dx = hh-i;
		double dy = hh-j;
		double r = sqrt(dx*dx+dy*dy);
		w_mask.at<double>(i,j) = w_fun(r);
	}

	int i = source.total();
	vector<vector<Mat>> c_xbar(source.rows, vector<Mat>(source.cols));
	vector<vector<Mat>> b(source.rows, vector<Mat>(source.cols));
	vector<vector<Mat>> approx_c(source.rows, vector<Mat>(source.cols));

	for (int y = 0; y<row; ++y)
		for (int x = 0; x<col; ++x)
		{
			b[y][x] = Mat(6,1, CV_64FC1, Scalar(1));
			b[y][x].at<double>(1,0) = double(x);
			b[y][x].at<double>(2,0) = double(y);
			b[y][x].at<double>(3,0) = double(x*y);
			b[y][x].at<double>(4,0) = double(x*x);
			b[y][x].at<double>(5,0) = double(y*y);
		}

	for (int y1 = 0; y1<row; ++y1)
	for (int x1 = 0; x1<col; ++x1)
	{
		Mat tem_b(6,6,CV_64FC1, Scalar()), tem_f(6,1,CV_64FC1, Scalar());

		for (int y2 = 0; y2<w_mask.rows; ++y2)
		for (int x2 = 0; x2<w_mask.cols; ++x2)
		{			
			int rx = x1-hh+x2;
			int ry = y1-hh+y2;
			if (rx>=0 && ry>=0 && rx<col && ry<row)
			{
				double w = w_mask.at<double>(y2,x2);				

				tem_f += w*source.at<double>(ry,rx)*b[ry][rx];
				tem_b += w*b[ry][rx]*b[ry][rx].t();
			}
		}

		solve(tem_b, tem_f, c_xbar[y1][x1]);
	}

	Mat w_mask_normalized = w_mask*(1.0/sum(w_mask).val[0]);

	for (int y1 = 0; y1<row; ++y1){
	for (int x1 = 0; x1<col; ++x1)
	{
		approx_c[y1][x1] = Mat(6,1,CV_64FC1, Scalar());

		for (int y2 = 0; y2<w_mask.rows; ++y2){
		for (int x2 = 0; x2<w_mask.cols; ++x2)
		{			
			int rx = x1-hh+x2;
			int ry = y1-hh+y2;
			if (rx>=0 && ry>=0 && rx<col && ry<row)
			{
				double w = w_mask_normalized.at<double>(y2,x2);
				approx_c[y1][x1] += w*c_xbar[ry][rx];
			}
		}}
	}}

	SaveC("coef_map.txt", approx_c);

	result = Mat(source.size(), CV_64FC1);
	pdx = Mat(source.size(), CV_64FC1);
	pdy = Mat(source.size(), CV_64FC1);

	for (int y = 0; y<row; ++y)
	for (int x = 0; x<col; ++x)
	{
		result.at<double>(y,x) = Mat(b[y][x].t()*approx_c[y][x]).at<double>(0);
		pdx.at<double>(y,x) = approx_c[y][x].at<double>(1,0) + approx_c[y][x].at<double>(3,0)*y + 2*approx_c[y][x].at<double>(4,0)*x;
		pdy.at<double>(y,x) = approx_c[y][x].at<double>(2,0) + approx_c[y][x].at<double>(3,0)*x + 2*approx_c[y][x].at<double>(5,0)*y;
	}
}

void PostProcessing::GetMeshData( const cv::Mat& depthmap, std::vector<XnPoint3D>& pt_projected, std::vector<XnPoint3D>& pt_real, std::vector<std::vector<int>>& tri_indx )
{
	// initialize data vector
	int w = depthmap.cols;
	int h = depthmap.rows;
	int t = w*h;
	pt_projected.clear();
	pt_projected.reserve(t);
	tri_indx.clear();
	tri_indx.reserve(t*2);

	int nx = 0, ny = 0;
	XnPoint3D tem;
	double up, down, left, right;
	double thr = 5;
	std::vector<int> tri(3,0);

	// check map
	Mat checkmap(depthmap.size(), CV_8UC1, Scalar());

	// get data
	for (int i = 0; i<h; ++i)
		for (int j = 0; j<w; ++j)
		{
// 			nx = j+roi.x;
// 			ny = i+roi.y;
			nx = j;
			ny = i;

			// get position data		
			if (depthmap.at<double>(i,j) < mx_dist*0.9)
			{			
				if (i>0 && j>0)
				{
					if (abs(depthmap.at<double>(i,j)-depthmap.at<double>(i,j-1)) < thr && abs(depthmap.at<double>(i,j)-depthmap.at<double>(i-1,j)) < thr)					
					{
						tem.X = nx;
						tem.Y = ny;
						tem.Z = depthmap.at<double>(i,j);		
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i,j)==0) checkmap.at<uchar>(i,j) = 255;					

						tem.Y -= 1; tem.Z = depthmap.at<double>(i-1,j);
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i-1,j)==0) checkmap.at<uchar>(i-1,j) = 255;

						tem.X -= 1; tem.Y += 1; tem.Z = depthmap.at<double>(i,j-1);
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i,j-1)==0) checkmap.at<uchar>(i,j-1) = 255;

// 						tri[0] = i*w+j;
// 						tri[2] = (i-1)*w+j;
// 						tri[1] = i*w+(j-1);
						tri[0] = i*w+j;
						tri[1] = (i-1)*w+j;
						tri[2] = i*w+(j-1);
						tri_indx.push_back(tri);
					}
				}

				if (i<h-1 && j<w-1)
				{
					if (abs(depthmap.at<double>(i,j)-depthmap.at<double>(i,j+1)) < thr && abs(depthmap.at<double>(i,j)-depthmap.at<double>(i+1,j)) < thr)
					{
						tem.X = nx;
						tem.Y = ny;
						tem.Z = depthmap.at<double>(i,j);		
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i,j)==0) checkmap.at<uchar>(i,j) = 255;					

						tem.Y += 1; tem.Z = depthmap.at<double>(i+1,j);
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i+1,j)==0) checkmap.at<uchar>(i+1,j) = 255;					

						tem.X += 1; tem.Y -= 1; tem.Z = depthmap.at<double>(i,j+1);
						pt_projected.push_back(tem);
						if (checkmap.at<uchar>(i,j+1)==0) checkmap.at<uchar>(i,j+1) = 255;

// 						tri[0] = i*w+j;
// 						tri[2] = (i+1)*w+j;
// 						tri[1] = i*w+(j+1);
						tri[0] = i*w+j;
						tri[1] = (i+1)*w+j;
						tri[2] = i*w+(j+1);
						tri_indx.push_back(tri);
					}
				}
			}
		}

		// sorting projected points and face indx
		std::sort(pt_projected.begin(), pt_projected.end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
			if(ei.Y < ej.Y) return true;
			else if(ei.Y > ej.Y) return false;
			else return (ei.X < ej.X);
		});
		std::vector<XnPoint3D>::iterator it = std::unique(pt_projected.begin(), pt_projected.end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
			return (ei.X == ej.X && ei.Y == ej.Y);
		});
		pt_projected.erase(it, pt_projected.end());

		bitwise_not(checkmap, checkmap);
		checkmap.convertTo(checkmap, CV_8UC1, 1.0/255.0);

		for (int i = 0; i<tri_indx.size(); ++i)
		{
			for (int j = 0 ; j<3; ++j)
			{
				int ix = tri_indx[i][j]%w;
				int iy = tri_indx[i][j]/w;
				Rect temroi(0,0,w,iy);
				Rect temroi2(0,iy,ix+1,1);
				int s = sum(Mat(checkmap, temroi)).val[0]+sum(Mat(checkmap, temroi2)).val[0];

				tri_indx[i][j] -= s;
			}
		}	

		pt_real.resize(pt_projected.size());
// 		kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected.size(), pt_projected.data(), pt_real.data());
		pt_real = pt_projected;

}

void PostProcessing::SaveC( const char* filename, const std::vector<std::vector<cv::Mat>>& c )
{
	ofstream fout(filename);
	for (int i = 0; i<c.size(); ++i)
	{
		for (int j = 0; j<c[i].size(); ++j)
		{
			for (int k = 0; k<c[i][j].rows; ++k)
			{
				fout << c[i][j].at<double>(k) << " ";
			}
		}
		fout << endl;
	}
	fout.close();
}
