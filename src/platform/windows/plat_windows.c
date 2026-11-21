/* Windows preview through Cygwin: reuse the native SDL2/OpenGL renderer.
 * Cygwin supplies POSIX networking and threading used by Origin's core. */
#include "platform/plat.h"
#include "core/keys.h"
#include "core/applog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
static char assets[1024], data[1024];
void plat_pre_init(const char *id) {
  (void)id;
  const char *p = getenv("SB_ASSETS");
  snprintf(assets, sizeof assets, "%s", p && *p ? p : "assets");
  p = getenv("LOCALAPPDATA");
  if (!p || !*p) p = getenv("HOME");
  snprintf(data, sizeof data, "%s/StremioCinemaPreview", p && *p ? p : ".");
  if (mkdir(data, 0700) != 0 && errno != EEXIST) fprintf(stderr,"[windows] data folder not writable: %s\n",data);
  applog_start(data);
}
void plat_post_window(SDL_Window *w) { (void)w; }
const char *plat_asset_dir(void) { return assets; }
const char *plat_data_dir(void) { return data; }
void plat_window_size(int *w, int *h, Uint32 *flags) {
  int ww=1280, hh=720; const char *env=getenv("SB_WINDOW");
  if (env && sscanf(env,"%dx%d",&ww,&hh)!=2) { ww=1280; hh=720; }
  if(ww<320||hh<240) { ww=1280; hh=720; }
  *w=ww; *h=hh; *flags=SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;
  if (!getenv("SB_SHOW")) *flags |= SDL_WINDOW_HIDDEN;
}
int plat_map_key(const SDL_KeyboardEvent *e) {
  switch(e->keysym.sym) {
    case SDLK_LEFT:return K_LEFT;case SDLK_RIGHT:return K_RIGHT;
    case SDLK_UP:return K_UP;case SDLK_DOWN:return K_DOWN;
    case SDLK_RETURN:case SDLK_KP_ENTER:return K_OK;
    case SDLK_ESCAPE:case SDLK_BACKSPACE:return K_BACK;
    case SDLK_SPACE:return K_PLAYPAUSE;
    case SDLK_F1:return K_RED;case SDLK_F2:return K_GREEN;
    case SDLK_F3:return K_YELLOW;case SDLK_F4:return K_BLUE;
    case SDLK_COMMA:return K_REW;case SDLK_PERIOD:return K_FF;
    case SDLK_PAGEUP:return K_CH_UP;case SDLK_PAGEDOWN:return K_CH_DOWN;
    default:return K_NONE;
  }
}
int plat_text_input(void) { return getenv("SB_NO_TEXTINPUT")?0:1; }
const char *plat_device_name(void) { return "Windows native preview"; }
const char *plat_log_header(void) { return ""; }
int plat_mem_total_mb(void) { return 0; }
void plat_thread_background(int nice) { (void)nice; }
int plat_lifecycle(const SDL_Event *e) {
 if(e->type==SDL_APP_DIDENTERFOREGROUND)return 1;
 if(e->type==SDL_APP_DIDENTERBACKGROUND)return -1;
 if(e->type==SDL_WINDOWEVENT) {
  if(e->window.event==SDL_WINDOWEVENT_RESTORED)return 1;
  if(e->window.event==SDL_WINDOWEVENT_MINIMIZED)return -1;
 }
 return 0;
}
const char *plat_ui_locale(void) { return NULL; }
char *plat_luna_call(const char *u,const char *p,int t) { (void)u;(void)p;(void)t;return NULL; }
unsigned long plat_luna_subscribe(const char *u,const char *p,PlatLunaCb cb,void *d) {(void)u;(void)p;(void)cb;(void)d;return 0;}
unsigned long plat_luna_subscribe_app(const char *u,const char *p,PlatLunaCb cb,void *d) {(void)u;(void)p;(void)cb;(void)d;return 0;}
int plat_luna_send_app(const char *u,const char *p) {(void)u;(void)p;return 0;}
void plat_luna_cancel(unsigned long h) {(void)h;}
void plat_luna_pump(void) {}
int plat_luna_send(const char *u,const char *p) {(void)u;(void)p;return 0;}
int plat_panel_lines(void){return 0;}
void plat_pointer_visible(int on){(void)on;}
