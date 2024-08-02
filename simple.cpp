#include <tesseract/baseapi.h>
#include <allheaders.h> // in leptonica src

int main() {
  char *outText;

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

  // Initialize tesseract-ocr with English, without specifying tessdata path
  if (api->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    exit(1);
  }

  Pix *image = pixRead("../sample.png");
  api->SetImage(image);

  outText = api->GetUTF8Text();
  printf("OCR output:\n%s", outText);

  api->End();
  delete api;
  delete[] outText;
  pixDestroy(&image);

  return 0;
}
