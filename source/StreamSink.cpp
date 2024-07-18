#include "StreamSink.hpp"

namespace OwLog {

StreamSink::StreamSink(std::ostream& stream)
    : mStream(stream) {}

void StreamSink::write(std::string_view message) {
    mStream << message;
}

} // namespace OwLog