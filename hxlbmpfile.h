#define _CRT_SECURE_NO_WARNINGS

#ifndef HXLBMPFILEH
#define HXLBMPFILEH

#include "stdio.h"
#include "windows.h"

class HXLBMPFILE
{
	BYTE *pImageData;
	BOOL IsBMPFile(FILE *f);
	int GetBytes1Line();
	BOOL GetPara(FILE *f);
	BOOL Get8BMPData(FILE *f);
	BOOL Get24BMPData(FILE *f);
	void SaveFileHeader(FILE *f);
	void SaveInfoHeader(FILE *f);
	BOOL Save8BMPData(FILE *f);
	BOOL Save24BMPData(FILE *f);

public:
	int iImagew, iImageh;
	int iYRGBnum;
	RGBQUAD rgbPalette[256];
	BYTE *pDataAt(int h, int Y0R0G1B2 = 0);
	BOOL IspImageDataOk();
	BOOL LoadBMPFile(const char *fname);
	BOOL SaveBMPFile(const char *fname);

	HXLBMPFILE();
	~HXLBMPFILE();
};
#endif
