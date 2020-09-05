#include <postgres.h>
#include <math.h>
#include "wilson_score_interval.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(wilson_score_interval_upper_bounds);

PG_FUNCTION_INFO_V1(wilson_score_interval_lower_bounds);

Datum wilson_score_interval_upper_bounds(PG_FUNCTION_ARGS)
{

	const int32 trials = PG_GETARG_INT32(0);

	const int32 success = PG_GETARG_INT32(1);

	const double z_score = PG_GETARG_FLOAT8(2);

	wilson_validate_range(trials, success, z_score);

	if(trials == 0)
	{
		PG_RETURN_FLOAT8(0.0);
	}

	PG_RETURN_FLOAT8(
		wilson_score_interval(trials, success, z_score, 1)
	);
}

Datum wilson_score_interval_lower_bounds(PG_FUNCTION_ARGS)
{
	const int32 trials = PG_GETARG_INT32(0);

	const int32 success = PG_GETARG_INT32(1);

	const double z_score = PG_GETARG_FLOAT8(2);

	wilson_validate_range(trials, success, z_score);

	if(trials == 0)
	{
		PG_RETURN_FLOAT8(0.0);
	}

	PG_RETURN_FLOAT8(
		wilson_score_interval(trials, success, z_score, -1)
	);
}

double wilson_score_interval(int32 trials, int32 success, double z_score, int32 sign)
{
	const double phat = (double) success / (double) trials;

	const double z2 = z_score * z_score;

	const double denominator = 1.0 + z2 / trials;

	const double centre_probability = phat + z2 / (2.0 * trials);

	const double std_dev = sqrt((phat * (1.0 - phat) + z2 / (4.0 * trials)) / trials);

	return (centre_probability + (sign * (z_score * std_dev))) / denominator;
}


void wilson_validate_range(int32 trials, int32 success, double z_score)
{	

	if(trials < 0)
	{
		ereport(ERROR, (
			errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			errmsg("negative trials are not allowed"),
			errdetail("trial value %d is negative", trials),
			errhint("trials must be positive")
		));
	}

	if(success < 0)
	{
		ereport(ERROR, (
			errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			errmsg("negative succeses are not allowed"),
			errdetail("success value %d is negative", success),
			errhint("success must be positive")
		));
	}

	if(trials < success)
	{
		ereport(ERROR, (
			errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			errmsg("success must not be greater than trials"),
			errdetail("success value %d is greater than trials %d", success, trials),
			errhint("make success less than trials")
		));
	}

	if(z_score < 3 && z_score > 3)
	{
		ereport(ERROR, (
			errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			errmsg("z-score must be within range of -3 to 3"),
			errdetail("z-score value %f", z_score),
			errhint("make z-score be within acceted range")
		));
	}
}