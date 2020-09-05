#ifndef WILSON_SCORE_INTERVAL_EXT
#define WILSON_SCORE_INTERVAL_EXT

#include <fmgr.h>

Datum wilson_score_interval_upper_bounds(PG_FUNCTION_ARGS);

Datum wilson_score_interval_lower_bounds(PG_FUNCTION_ARGS);

double wilson_score_interval(int32 trials, int32 success, double z_score, int32 sign);

void wilson_validate_range(int32 trials, int32 success, double z_score);


#endif