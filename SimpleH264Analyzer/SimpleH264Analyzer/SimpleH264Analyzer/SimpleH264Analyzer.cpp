// SimpleH264Analyzer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "Stream.h"
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
    CStreamFile h264stream(argv[1]);

    h264stream.Parse_h264_bitstream();

    return 0;
}
