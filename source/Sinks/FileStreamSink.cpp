/**
 * @file FileStreamSink.cpp
 * @author TL044CN
 * @brief FileStreamSink class implementation
 * @version 0.1
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Sinks/FileStreamSink.hpp"

namespace OwLog {

FileStreamSink::FileStreamSink(const std::string& filename)
    : StreamSink(mFile)
    , mFile(filename) {}

FileStreamSink::~FileStreamSink() {
    mFile.close();
}

bool FileStreamSink::good() const {
    return mFile.good();
}

} // namespace OwLog
