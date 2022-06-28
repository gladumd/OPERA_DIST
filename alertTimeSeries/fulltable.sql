PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE fulltable(
  HLS_ID TEXT PRIMARY KEY,
  DIST_ID TEXT NOT NULL UNIQUE,
  statusFlag INTEGER,
  MGRStile TEXT,
  sensingTime TEXT,
  availableTime TEXT, 
  downloadTime TEXT,
  processedTime TEXT, 
  softwareVersion TEXT, 
  percentData REAL, 
  percentAnomaly REAL,
  Errors TEXT
);

