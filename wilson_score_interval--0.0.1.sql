
CREATE OR REPLACE FUNCTION wilson_score_interval_upper_bounds(int,int,float8) 
	RETURNS float8 
	AS 'MODULE_PATHNAME'	
	LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION wilson_score_interval_lower_bounds(int,int,float8) 
	RETURNS float8 
	AS 'MODULE_PATHNAME'
	LANGUAGE C STRICT;