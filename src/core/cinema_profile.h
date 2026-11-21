#ifndef SB_CINEMA_PROFILE_H
#define SB_CINEMA_PROFILE_H
/* Returns the directory of this process's active profile.
 * Without SB_CINEMA_PROFILE, reuses the normal directory for compatibility.
 * With an invalid ID or a filesystem failure, returns NULL (fail closed).
 * Profile selection is at process start: never swap a live auth session.
 */
const char *cinema_profile_data_dir(const char *base);
#endif
