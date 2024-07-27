/**
 * @file FileStreamSink.hpp
 * @author TL044CN
 * @brief FileStreamSink class declaration
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "StreamSink.hpp"
#include <fstream>

namespace OwLog {

/**
 * @ingroup Sinks
 * @brief FileStreamSink class
 * @details FileStreamSink class is a class that writes log messages to a file
 */
class FileStreamSink : public StreamSink {
private:
    std::ofstream mFileStream;

public:
    /**
     * @brief Construct a new FileStreamSink object
     * @param filename File name
     */
    FileStreamSink(const std::string& filename);

    /**
     * @brief Destroy the FileStreamSink object
     */
    ~FileStreamSink();

    /**
     * @brief Check if the file is good
     * @return true if the file is good, false otherwise
     */
    bool good() const;

};

} // namespace OwLog