#pragma once

#include "ws2811.h"

#define DEFAULT_FREQ 1200000
#define DEFAULT_GPIO 10
#define DEFAULT_DMA 10
#define DEFAULT_LEDCOUNT 50
#define DEFAULT_STRIPTYPE WS2811_STRIP_BGR
#define DEFAULT_INVERT 0
#define DEFAULT_BRIGHTNESS 255

typedef struct strip_t strip_t;

enum strip_state_t {
	STRIP_OFF,
	STRIP_ON,
};

struct strip_t {
	ws2811_t strip;
	ws2811_led_t* alt_buf[RPI_PWM_CHANNELS];
	int state[RPI_PWM_CHANNELS];
};

#define strip_inner_param(s,p) (s)->strip.(p)
#define stripp_inner_param(s,p) (s).strip.(p)

#define strip_channel_count(s,c) ((s)->strip.channel[c].count)
#define strip_crightbuf(s,c) \
	(strip_cis_on((s),(c)) ? (s)->strip.channel[c].leds : (s)->alt_buf[c])

#define strip_cis_on(s,c) ((s)->state[c] == STRIP_ON)

#define strip_renderPM(s) (ws2811_render(&((s)->strip)))
#define strip_renderNPM(s) (ws2811_render(&((s).strip)))

#define strip_last_channel(s) (RPI_PWM_CHANNELS - 1)

void strip_state_set(strip_t* strip, int state);
int strip_state_get(strip_t* strip);

void strip_buffer_start_set(strip_t* strip, int channel, ws2811_led_t* buffer,
	int blen);
void strip_buffer_sub_set(strip_t* strip, int channel, ws2811_led_t* buffer,
	int blen, int start, int end);

void strip_render(strip_t* strip);

void strip_init(strip_t* strip);
void strip_fini(strip_t* strip);

int strip_resize(strip_t* strip, int channel, int newlen);