#ifndef _JPEG_H_
#define _JPEG_H_

#include <jpeglib.h>
#include "imgdib.h"

bool LoadJpeg(CImageDIB *pImage, const char *filename);
bool SaveJpeg24(const CImageDIB *pImage, const char *filename, int quality = 100);

#endif /* _JPEG_H_ */
