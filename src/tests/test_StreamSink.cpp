#include <blackhole/sink/stream.hpp>

#include "global.hpp"

using namespace blackhole;

TEST(stream_t, Class) {
   sink::stream_t sink1(sink::stream_t::output_t::stdout);
   sink::stream_t sink2(sink::stream_t::output_t::stderr);
   UNUSED(sink1);
   UNUSED(sink2);
}

TEST(stream_t, StringConstructor) {
    sink::stream_t sink1("stdout");
    sink::stream_t sink2("stderr");
    UNUSED(sink1);
    UNUSED(sink2);
}

TEST(stream_t, CanConsumeLogMessage) {
    sink::stream_t sink(sink::stream_t::output_t::stdout);
    sink.consume("test message for stream sink");
}
