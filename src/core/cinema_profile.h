#ifndef SB_CINEMA_PROFILE_H
#define SB_CINEMA_PROFILE_H
/* Returns the directory of this process's active profile.
 * Without SB_CINEMA_PROFILE, reuses the normal directory for compatibility.
 * With an invalid ID or a filesystem failure, returns NULL (fail closed).
 * Profile selection is at process start: never swap a live auth session.
 */
const char *cinema_profile_data_dir(const char *base);
/* Persist the next process\x27s active profile, without touching live auth state. */
int cinema_profile_set_active(const char *base, const char *id);
#ifdef SB_CINEMA_NATIVE
int cinema_activate_profile(const char *id); /* relaunch process after store flush */
#endif
#endif
