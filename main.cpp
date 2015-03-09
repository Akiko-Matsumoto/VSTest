#include "stdafx.h"
#include "opencv_lib.hpp"								// OpenCVヘッダ

int _tmain(int argc, _TCHAR* argv[])
{
	Mat frame;											// 画像リソース宣言
	VideoCapture src(1);								// 映像取得（カメラ映像）
	if (src.isOpened() == 0){ cout << "映像が取得できません。\n" << endl; waitKey(0); return -1;}

	while (frame.data == NULL){ src >> frame; }			// 初期フレーム取得

	int w = frame.cols, h = frame.rows;					// 映像フレームの幅と高さ

	while (1){

		src >> frame; if (frame.data == NULL) break;	// 1フレーム取得
		//中心座標のRGB値表示（変換前）
		printf("RGB=(%3d, %3d, %3d) → ", Ri(frame, w / 2, h / 2),
				Gi(frame, w / 2, h / 2), Bi(frame, w / 2, h / 2));

		for (int y = h / 3; y < h * 2 / 3; y++){		//ピクセル値変換領域垂直方向
			for (int x = w / 3; x < w * 2 / 3; x++){	//ピクセル値変換領域水平方向
				if (Ri(frame, x, y) > 200){				//赤のピクセル値が200より大きい場合
					Ri(frame, x, y) = 255;
					Gi(frame, x, y) = 255;
					Bi(frame, x, y) = 255;
				}
				else{									//赤のピクセル値が200以下の場合
					Ri(frame, x, y) = 0;
					Gi(frame, x, y) = 0;
					Bi(frame, x, y) = 0;
				}
			}
		}
		//中心座標のRGB値表示（変換後）
		printf("RGB=(%3d, %3d, %3d)\n", Ri(frame, w / 2, h / 2),
				Gi(frame, w / 2, h / 2), Bi(frame, w / 2, h / 2));

		imshow("入力映像", frame);						// 1フレーム表示

		if(waitKey(30) == 27) break;					// キー入力待機（30ms）
	}

	return 0;
}
