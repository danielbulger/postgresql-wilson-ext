MODULES = wilson_score_interval
EXTENSION = wilson_score_interval
DATA = wilson_score_interval--0.0.1.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)