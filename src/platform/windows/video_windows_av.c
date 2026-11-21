/* Cygwin Windows UI preview has no AVFoundation.
 * All real video playback functions are unavailable in this target.
 * With SB_REAL_VIDEO=0 (the default), video_windows.c provides a fully
 * navigable simulated stream UI; never claim actual video playback. */
#include "core/video.h"
#include <stdint.h>
#include <string.h>
void av_load(const char*u){(void)u;}
void av_unload(void){}
void av_play(void){}
void av_pause(void){}
void av_seek(double s){(void)s;}
void av_rejoin(void){}
double av_time(void){return 0;}
double av_duration(void){return 0;}
double av_buffered(void){return 0;}
VidState av_state(void){return VID_ERROR;}
const char*av_error(void){return "Real video is unavailable in the Windows UI preview";}
int av_live(void){return 0;}
int av_has_media(void){return 0;}
int av_width(void){return 0;}
int av_height(void){return 0;}
double av_fps(void){return 0;}
void av_volume(int p,int ms){(void)p;(void)ms;}
int av_audio_tracks(VidTrack*out,int max){(void)out;(void)max;return 0;}
int av_audio_current(void){return 0;}
void av_select_audio(int idx){(void)idx;}
void av_window(float x,float y,float w,float h){(void)x;(void)y;(void)w;(void)h;}
void av_crop(int sx,int sy,int sw,int sh,float dx,float dy,float dw,float dh)
{(void)sx;(void)sy;(void)sw;(void)sh;(void)dx;(void)dy;(void)dw;(void)dh;}
void av_pump(void){}
int av_edges(uint32_t *o){(void)o;return 0;}
int av_native(void){return 0;}
void video_mac_radius(float r){(void)r;}
void video_mac_underlay(void){}
void video_mac_hole(float x,float y,float w,float h)
{(void)x;(void)y;(void)w;(void)h;}
int video_mac_real(void){return 0;}
