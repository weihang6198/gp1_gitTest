#include "common.h"

//  �萔
const FLOAT PI{ DirectX::XM_PI };
const LONG SCREEN_W{ 1280 };
const LONG SCREEN_H{ 720 };
const BOOL FULLSCREEN{ FALSE };
const LPCWSTR APPLICATION_NAME{ L"C++ project template" };

//  �֐��|�C���^
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // �p�x�����W�A����
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ���W�A�����p�x��
