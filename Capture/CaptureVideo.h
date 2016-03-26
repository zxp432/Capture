#pragma once
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "client.cpp"
#include <windows.h>
#include <queue>

CvCapture* capture;
IplImage* frame;
double fps;
int now_frame_no = 0;
int fame_continue = 0;
std::queue<IplImage> imageQueue;

namespace Capture1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;
	using namespace SocketCommu;
	
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:ref struct Result
		{
			int x1;
			int y1;
			int x2;
			int y2;
			System::String ^score;
			System::String ^cls;  /*'aeroplane', 'bicycle', 'bird', 'boat',
								  'bottle', 'bus', 'car', 'cat', 'chair',
								  'cow', 'diningtable', 'dog', 'horse',
								  'motorbike', 'person', 'pottedplant',
								  'sheep', 'sofa', 'train', 'tvmonitor'*/
		};  //最后有一个分号
	private:Client ^client = gcnew Client();
			array<Result ^> ^boxes;
			String ^result = "";// "12-12-15-115-0.98-person,12-12-15-115-0.98-person,";
			System::Windows::Forms::Timer^  timer2;
			HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	public:
		Form1(void)
		{
			InitializeComponent();			
		}

	protected:		
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	#pragma region Window_control
	private: System::Windows::Forms::Panel^  panel1;






	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	#pragma endregion

	protected: 

	private:

		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->groupBox3);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(536, 626);
			this->panel1->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->comboBox1);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(3, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(524, 62);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"检测源";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(436, 23);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(79, 30);
			this->button2->TabIndex = 1;
			this->button2->Text = L"开始";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"打开摄像头进行检测", L"选择视频进行检测" });
			this->comboBox1->Location = System::Drawing::Point(13, 23);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(417, 27);
			this->comboBox1->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(5, 61);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(5);
			this->groupBox1->Size = System::Drawing::Size(522, 558);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"视频";
			// 
			// trackBar1
			// 
			this->trackBar1->AutoSize = false;
			this->trackBar1->Location = System::Drawing::Point(13, 534);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(501, 26);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Visible = false;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 38);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 500);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 10;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 23);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(542, 632);
			this->Controls->Add(this->panel1);
			this->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(5);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Padding = System::Windows::Forms::Padding(3);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"实时物体检测";
			this->panel1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if(comboBox1->Text == "")
		{
			MessageBox::Show(this,"Select Capture Method","Error!!!");
		}
		if(button2->Text == "开始")
		{
			if (comboBox1->Text == "打开摄像头进行检测")
			{					
				capture = cvCaptureFromCAM(0);
				fps = 30;// cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //视频帧率
				fame_continue = ceil(fps / 5);
				trackBar1->Visible = false;
				trackBar1->Minimum = 0;
				trackBar1->Maximum = 0;
				button2->Text = "停止";
				timer1->Start();
				pictureBox1->Location = System::Drawing::Point(12, 38);
			}
			else if (comboBox1->Text == "选择视频进行检测")
			{
				openFileDialog1->Filter = "AVI files (*.avi)|*.txt|All files (*.*)|*.*";
				openFileDialog1->FilterIndex = 2;
				openFileDialog1->RestoreDirectory = true;
				openFileDialog1->FileName ="";
				trackBar1->Visible = true;
				pictureBox1->Location = System::Drawing::Point(12, 28);
				if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{		
					char *fileName = (char*) Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer();					
					capture = cvCaptureFromFile(fileName);
					fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //视频帧率
					fame_continue = ceil(fps / 5);
					trackBar1->Minimum = 0;
					trackBar1->Maximum = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
					button2->Text = "停止";
					timer1->Start();
				}				
			}
		}
		else if(button2->Text == "停止")
		{
			cvReleaseCapture(&capture);		
			button2->Text = "开始";
			timer1->Stop();
			timer2->Stop();
			now_frame_no = 0;
		}
	}
	
	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) 
	{
		cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES, trackBar1->Value);
	}

	private: System::Void cvText(IplImage* img, const char* text, int x, int y)//写字的
	{
		CvFont font;

		double hscale = 1.0;
		double vscale = 1.0;
		int linewidth = 2;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hscale, vscale, 0, linewidth);

		CvScalar textColor = CV_RGB(247, 186, 64);
		CvPoint textPos = cvPoint(x, y);

		cvPutText(img, text, textPos, &font, textColor);
	}

	private: System::Void cvFrame(IplImage* img, int x1, int y1, int x2, int y2)//画框的
	{
		cvRectangle(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB(247, 186, 64), 2);
	}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		try
		{		
			frame = cvQueryFrame(capture);
			if(frame != NULL)
			{
				imageQueue.push(*frame);
				if (now_frame_no % fame_continue == 0)//发送帧，改变框子参数
				{
					timer2->Start();
				}
				if (imageQueue.size() == 6) {
					*frame = imageQueue.front();
					imageQueue.pop();
					WaitForSingleObject(hMutex, INFINITE);
					for each (Result ^box in boxes)
					{
						//画框子
						cvFrame(frame, box->x1, box->y1, box->x2, box->y2);
						//cvFrame(frame, 50, 50, 400, 200);
						//写字
						char cls[40];
						box->cls = box->cls;
						for (int i = 0; i < box->cls->Length; i++)
						{
							cls[i] = box->cls[i];
						}
						cls[box->cls->Length] = '\0';
						cvText(frame, cls, box->x1, box->y1);
					}
					ReleaseMutex(hMutex);

					pictureBox1->Image = gcnew System::Drawing::Bitmap(frame->width, frame->height, frame->widthStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) frame->imageData);
					pictureBox1->Refresh();

//					trackBar1->Value = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
					double codec_double = cvGetCaptureProperty(capture, CV_CAP_PROP_FOURCC);
					//label6->Text = "Codec: " + System::Text::Encoding::UTF8->GetString(BitConverter::GetBytes((int)codec_double));
					now_frame_no++;
				}
			}
		}catch(Exception ^g){
			client->closeSocket();
		}
	}
	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		WaitForSingleObject(hMutex, INFINITE);
		client->connect();
		client->sendImg(frame);
		result = client->receive();
		if (!result->Equals(""))
		{
			array<String ^> ^boxString = result->Split(',');
			boxes = gcnew array<Result ^>(boxString->Length - 1);
			for (int i = 0; i < boxString->Length - 1; i++)
			{
				Result ^temp = gcnew Result();
				array<String ^> ^box = boxString[i]->Split('-');
				temp->x1 = int::Parse(box[0]);
				temp->y1 = int::Parse(box[1]);
				temp->x2 = int::Parse(box[2]);
				temp->y2 = int::Parse(box[3]);
				temp->score = box[4];
				temp->cls = box[5]+":"+box[4];
				boxes[i] = temp;
			}
		}
		else
		{
			boxes = gcnew array<Result ^>(1);
			Result ^temp = gcnew Result();
			temp->x1 = 0;
			temp->y1 = 0;
			temp->x2 = 0;
			temp->y2 = 0;
			temp->cls = "";
			temp->score = "";
			boxes[0] = temp;
		}
		client->closeSocket();
		ReleaseMutex(hMutex);
		timer2->Stop();
	}
};
}

