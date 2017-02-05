
#include <Timer.h>
#include <Adafruit_MPL3115A2.h>

//adafruit barometer
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

//zeroing the barometer
float zero;

//variables for logging height during launch
Timer t;
int time;
uint16_t logs[MAX_LOG];

void log() {
	//TODO compress based on predictability of data
	if(time => MAX_LOG) {
		t.stop(tick);
		return;
	}
	logs[time] = (baro.getAltitude() - zero) * LOG_SCALE;

	time++;
}

void start_log() {
	baro.begin();
    zero = baro.getAltitude();
	//start off current time
    currTime=0;
    //logs
    tick = t.every(LOG_MS, log);
}

float get_height() {
	return baro.getAltitude() - zero;
}

void update_timer() {
	t.update();
}
