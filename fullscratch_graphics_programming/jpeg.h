#ifndef _JPEG_H_
#define _JPEG_H_

#include <jpeglib.h>
#include "img32.h"

bool LoadJpeg(CImage32 *pImage, const char *filename);
bool SaveJpeg24(const CImage32 *pImage, const char *filename, int quality = 100);

#endif /* _JPEG_H_ */
