#ifndef CC_CC_INTERFACE_H
#define CC_CC_INTERFACE_H

#define cimg_use_jpeg
#define cimg_use_png

#include "CImg.h"
#include "project_constants.h"


enum class CC_AlgorithmType {
	kMeans,
	kMeansUnweighted,
	//kpp,
	//kMedians
};

enum class CC_FileType {
	bmp,
	jpeg,
	png
};

class CC_Interface {
private:
	cimg_library::CImg<int> original_image;
	cimg_library::CImg<int> result_image;
	cimg_library::CImgDisplay original_display;
	cimg_library::CImgDisplay result_display;
public:
	void ImageLoad(const char* filename);
	void Process(unsigned int k, CC_AlgorithmType algorithm_type);
	void Display();
	void Close();
	void Save(const char *filename, CC_FileType filetype) const;
	bool InputIsValid() const noexcept;
	bool CanSave() const noexcept;
};

#endif
