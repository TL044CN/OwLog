#include "Sinks/StreamSink.hpp"

namespace OwLog {

StreamSink::StreamSink(std::ostream& stream)
    : mStream(stream) {}

void StreamSink::flush() {
    mStream.flush();
}

void StreamSink::write(std::string_view message) {
    mStream << message;
}

} // namespace OwLog