#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>
#include "bitmap.h"
#include "jpeg.h"

bool LoadJpeg(CImageDIB *pImage, const char *filename) {
    if (pImage == NULL || filename == NULL) {
        return false;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return false;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, fp);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int row_stride = cinfo.output_width * cinfo.output_components;
    JSAMPARRAY ppBuffer = (*cinfo.mem->alloc_sarray)(reinterpret_cast<j_common_ptr> (&cinfo), JPOOL_IMAGE, row_stride, 1);
    pImage->Resize(cinfo.output_width, cinfo.output_height);

    unsigned int y = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, ppBuffer, 1);

        JSAMPROW pBuf = *ppBuffer;
        for (unsigned int x = 0; x < cinfo.output_width; x++) {
            TARGB pixel;
            if (cinfo.out_color_components == 3) {
                pixel.R = *pBuf++;
                pixel.G = *pBuf++;
                pixel.B = *pBuf++;
            } else {
                pixel.R = pixel.G = pixel.B = *pBuf++;
            }
            pixel.A = 255;
            pImage->PixelSet(x, y, pixel.ARGB);
        }
        y++;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);

    return true;
}

bool SaveJpeg24(const CImageDIB *pImage, const char *filename, int quality) {
    if (pImage == NULL || filename == NULL) {
        return false;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return false;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);

    cinfo.image_width = pImage->Width();
    cinfo.image_height = pImage->Height();
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    unsigned int y = 0;
    JSAMPROW pRow = new JSAMPLE[pImage->Width() * 3];
    while (cinfo.next_scanline < cinfo.image_height) {
        JSAMPROW pBuf = pRow;
        for (int x = 0; x < pImage->Width(); x++) {
            TARGB pixel;
            *pBuf++ = pixel.R;
            *pBuf++ = pixel.G;
            *pBuf++ = pixel.B;
        }
        jpeg_write_scanlines(&cinfo, &pRow, 1);
        y++;
    }

    jpeg_finish_compress(&cinfo);
    if(pRow != NULL) {
        delete[] pRow;
    }
    jpeg_destroy_compress(&cinfo);
    fclose(fp);

    return true;
}
