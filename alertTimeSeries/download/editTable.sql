PRAGMA foreign_keys=off;

BEGIN TRANSACTION;

ALTER TABLE fulltable RENAME TO old_table;

CREATE TABLE fulltable(
  HLS_ID TEXT PRIMARY KEY,
  DIST_ID TEXT,
  statusFlag INTEGER,
  MGRStile TEXT,
  sensingTime TEXT, --update to be the portion from the ID
  availableTime TEXT, 
  downloadTime TEXT,
  processedTime TEXT, 
  softwareVersion TEXT, 
  percentData REAL, 
  percentAnomaly REAL,
  Errors TEXT
  CONSTRAINT unique_HLS_ID UNIQUE (HLS_ID)
);

INSERT INTO fulltable SELECT * FROM old_table;

COMMIT;

PRAGMA foreign_keys=on;

--DROP TABLE old_products;