#pragma once

#include <string>
#include <atomic>
#include <memory>
#include <cstdint>
#include <fstream>
#include <thread>

#include "CameraInterface.h"

using std::string;

/**
* Format is:
* int32_t at file beginning for frame count
*
* For each frame:
* int64_t: timestamp
* int32_t: depthSize
* int32_t: imageSize
* depthSize * unsigned char: depth_compress_buf
* imageSize * unsigned char: encodedImage->data.ptr
*/

class Logger
{
public:
  Logger(string outDir,std::shared_ptr<CameraInterface> cam);
  ~Logger();

  bool isWriting() const
  {
    return doWrite;
  }

  void startWriting();
  void stopWriting();

private:
  void write();

  std::atomic<bool> doWrite;
  string outDir;
  int32_t nFrames;
  int fileId;
  std::ofstream file;
  std::thread *writeThread;
  std::shared_ptr<CameraInterface> cam;
};
