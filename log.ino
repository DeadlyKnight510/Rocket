
#include <Timer.h>
#include <Adafruit_MPL3115A2.h>
#include "log.hpp"
#include "common.hpp"
//adafruit barometer
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
int tick;
//variables for logging height during launch
Timer t;
int time;
void log_baro() {
	//TODO compress based on predictability of data
	if(time >= MAX_LOG) {
		t.stop(tick);
		return;
	}
	logs[time] = (baro.getAltitude() - zero) * LOG_SCALE;

	time++;
}

void start_baro() {
    baro.begin();
}
void start_log() {
    start_baro();
    zero = baro.getAltitude();
	//start off current time
    //logs
    tick = t.every(LOG_MS, log_baro);
}

float get_height() {
  	return baro.getAltitude() - zero;
}

void update_timer() {
	t.update();
}
