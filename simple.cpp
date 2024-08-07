#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <stdexcept>

int main() {
  cv::Mat image = cv::imread("../../sample.png");
  if (image.empty())
    throw std::runtime_error("could not read image");

  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

  tesseract::TessBaseAPI api = new tesseract::TessBaseAPI();
  if (api->Init(nullptr, "eng"))
    throw std::runtime_error("Could not initialize tesseract");

  api->SetImage(gray.data, gray.cols, gray.rows, gray.channels(), gray.step);

  std::unique_ptr<char[]> outText(api->GetUTF8Text());
  std::cout << "OCR output:\n" << outText.get() << std::endl;

  // Confidence score optional

  cv::imshow("Processed Image", gray);
  cv::waitKey(0);

  return 0;
}
