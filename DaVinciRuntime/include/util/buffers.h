#ifndef BUFFERS_H
#define BUFFERS_H

#include <deque>
#include <mutex>
#include "ShellyPlusDimmerData.h"
#include "ShellyPlusPlugData.h"
#include "ShellyPlusTemperatureData.h"

// Fixed-size ring buffers
extern std::deque<ShellyPlusDimmerData> dimmer_buffer;
extern std::deque<ShellyPlusPlugData> plug_buffer;
extern std::deque<ShellyPlusTemperatureData> temperature_buffer;
extern std::mutex buffer_mutex;

#endif // BUFFERS_H