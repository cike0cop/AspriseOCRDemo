// AspriseOCRDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "asprise_ocr_api.h"
#include <iostream>

using namespace std;

void testOcr() {
	// CHANGE TO THE ACTUAL PATH to the folder where the aocr.dll or aocr.so locates in
	const char * libFolder = "LIB_FOLDER";

	// CHANGE TO THE ACTUAL PATH to the input image, can be jpeg, gif, png, tiff or pdf.
	const char * fileImg = "PATH/image.jpg";

	LIBRARY_HANDLE libHandle = dynamic_load_aocr_library(libFolder);

	// one time setup
	int setup = c_com_asprise_ocr_setup(false);
	if (setup != 1) {
		cerr << "Failed to setup. code: " << setup << endl;
		return;
	}

	// starts the ocr engine; the pointer must be of long long type
	long long ptrToApi = c_com_asprise_ocr_start("eng", OCR_SPEED_FAST, NULL, NULL, NULL);
	if (ptrToApi == 0) {
		cerr << "Failed to start." << endl;
		return;
	}

	char * s = c_com_asprise_ocr_recognize(ptrToApi, fileImg, -1, -1, -1, -1, -1,
		OCR_RECOGNIZE_TYPE_ALL, OCR_OUTPUT_FORMAT_PDF,
		"PROP_PDF_OUTPUT_FILE=result.pdf|PROP_PDF_OUTPUT_TEXT_VISIBLE=true|\
      PROP_PDF_OUTPUT_RETURN_TEXT=text", "|", "=");

	cout << "Returned: " << s << endl;

	// do more recognition here ...

	// finally, stops the OCR engine.
	c_com_asprise_ocr_stop(ptrToApi);

	cout << "Unload: " << (dynamic_unload_aocr_library(libHandle) ? "OK" : "Failed") << endl;
}


int main()
{
	testOcr();
	std::cout << "Press ENTER to exit: ";
	std::cin.ignore();
    return 0;
}

