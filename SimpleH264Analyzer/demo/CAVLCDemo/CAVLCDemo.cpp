// CAVLCDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>

#include "CAVLC.h"
#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
    int coeffs[16] = {3, 2, 1, -1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    string cavlc_code = Encoding_cavlc_16x16(coeffs);
    cout << cavlc_code << endl;
    return 0;
}
