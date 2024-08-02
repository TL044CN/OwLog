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
: StreamSink(mFileStream), mFileStream(filename, std::ios::out) {}

FileStreamSink::~FileStreamSink() {
    mFileStream.close();
}

bool FileStreamSink::good() const {
    return mFileStream.good();
}

} // namespace OwLog
