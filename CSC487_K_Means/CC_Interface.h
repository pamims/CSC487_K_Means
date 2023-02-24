#ifndef CC_CC_INTERFACE_H
#define CC_CC_INTERFACE_H

#define cimg_use_jpeg
#define cimg_use_png

#include "CImg.h"
#include "project_constants.h"


class CC_Interface {
private:
	cimg_library::CImg<int> original_image;
	cimg_library::CImg<int> result_image;
	cimg_library::CImgDisplay original_display;
	cimg_library::CImgDisplay result_display;
public:
	void Process(const char *filename, unsigned int k, CC_AlgorithmType algorithm_type);
	void Display();
	void Close();
	void Save(const char *filename, CC_FileType filetype) const;
	bool CanSave() const noexcept;
};

#endif
