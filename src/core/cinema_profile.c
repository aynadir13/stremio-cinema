#include "core/cinema_profile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static char active_dir[1024];

static int safe_id(const char *s) {
  size_t n = strlen(s);
  if (n < 1 || n > 32) return 0;
  for (size_t i=0; i<n; ++i) {
    char c=s[i];
    if (!((c>='a'&&c<='z') || (c>='A'&&c<='Z') ||
          (c>='0'&&c<='9') || c=='-' || c=='_')) return 0;
  }
  return 1;
}
static int ensure_directory(const char *p) {
  struct stat st;
  if (mkdir(p,0700) != 0 && errno != EEXIST) return 0;
  if (stat(p,&st) != 0 || !S_ISDIR(st.st_mode)) return 0;
  return 1;
}
const char *cinema_profile_data_dir(const char *base) {
  const char *id=getenv("SB_CINEMA_PROFILE");
  if (!base || !*base) return NULL;
  if (!id || !*id) return base; /* Existing first-run sign-in stays working. */
  if (!safe_id(id)) { fprintf(stderr,"[cinema] invalid profile ID\n"); return NULL; }
  char profiles[1024];
  int n=snprintf(profiles,sizeof profiles,"%s/profiles",base);
  if (n<0 || (size_t)n>=sizeof profiles) return NULL;
  n=snprintf(active_dir,sizeof active_dir,"%s/%s",profiles,id);
  if (n<0 || (size_t)n>=sizeof active_dir) return NULL;
  if (!ensure_directory(profiles) || !ensure_directory(active_dir)) {
    fprintf(stderr,"[cinema] profile directory unavailable: %s\n",strerror(errno));
    return NULL;
  }
  return active_dir;
}
