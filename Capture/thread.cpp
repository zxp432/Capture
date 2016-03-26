#pragma once
#include "stdafx.h"
#include "result.h"
#include "opencv2/opencv.hpp"
#include "client.cpp"

namespace SocketCommu {
	using namespace System;
	using namespace System::Collections;
	using namespace SocketCommu;

	public ref class Thread
	{
		private:Client^client = gcnew Client();
		public:String^ sendFrame(IplImage* frame) {
			client->connect();
			client->sendImg(frame);
			String^ result = client->receive();
			client->closeSocket();
			return result;
		}
	};
}