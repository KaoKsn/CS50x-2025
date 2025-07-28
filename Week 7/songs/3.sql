-- List the names of the top 5 longest songs, in descending order of length.

-- Requirement: List only the name of the songs.

-- Query:
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;
