/**
 * @file FileStreamSink.hpp
 * @author TL044CN
 * @brief FileStreamSink class header file
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "StreamSink.hpp"
#include <fstream>

namespace OwLog {

/**
 * @brief FileStreamSink class for representing a logging sink that writes to a file stream
 */
class FileStreamSink : public StreamSink {
private:
    std::ofstream mFile;  ///< the file stream to write to

public:
    /**
     * @brief Construct a new FileStreamSink object
     *
     * @param filename the name of the file to write to
     */
    FileStreamSink(const std::string& filename)
        : mFile(filename, std::ios::out), StreamSink(mFile) {};

    /**
     * @brief Destroy the FileStreamSink object
     *
     */
    virtual ~FileStreamSink() {
        mFile.close();
    };
}

}