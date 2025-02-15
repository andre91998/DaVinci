#include "buffers.h"

// Fixed-size ring buffers
std::deque<ShellyPlusDimmerData> dimmer_buffer(100);
std::deque<ShellyPlusPlugData> plug_buffer(100);
std::deque<ShellyPlusTemperatureData> temperature_buffer(100);
std::mutex buffer_mutex;