#include "core/cinema_profile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

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
  static char saved_id[40];
  if (!id || !*id) {
    char selection[1024];
    int nsel = snprintf(selection, sizeof selection, "%s/cinema-active-profile", base);
    if (nsel < 0 || (size_t)nsel >= sizeof selection) return NULL;
    FILE *f = fopen(selection, "r");
    if (f) {
      if (!fgets(saved_id, sizeof saved_id, f)) saved_id[0] = 0;
      fclose(f);
      saved_id[strcspn(saved_id, "\r\n")] = 0;
      id = saved_id;
    }
  }
  if (!id || !*id || !strcmp(id, "default")) return base;
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

/* Only this small profile-ID file is shared; auth/cache remain per-process.
 * Atomic replacement avoids partially written selection on a crash. */
int cinema_profile_set_active(const char *base, const char *id) {
  if (!base || !*base || !id || !safe_id(id)) return 0;
  char path[1024], temp[1024];
  int n = snprintf(path, sizeof path, "%s/cinema-active-profile", base);
  int m = snprintf(temp, sizeof temp, "%s/cinema-active-profile.tmp", base);
  if (n < 0 || m < 0 || (size_t)n >= sizeof path || (size_t)m >= sizeof temp) return 0;
  int fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC
#ifdef O_NOFOLLOW
                | O_NOFOLLOW
#endif
                , 0600);
  if (fd < 0) return 0;
  char line[40];
  n = snprintf(line, sizeof line, "%s\n", id);
  ssize_t wrote = write(fd, line, (size_t)n);
  int ok = wrote == n && fsync(fd) == 0;
  if (close(fd)) ok = 0;
  if (!ok || rename(temp, path) != 0) { unlink(temp); return 0; }
  return 1;
}
