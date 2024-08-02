#include <tesseract/baseapi.h>

int main() {
  char *outText;

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  
  // Initialize tesseract-ocr with English, without specifying tessdata path
  // if (api->Init(NULL, "eng")) {
  //   fprintf(stderr, "Could not initialize tesseract.\n");
  //   exit(1);
  // }

  // api->End();
  // delete api;
  // delete[] outText;

  return 0;
}
