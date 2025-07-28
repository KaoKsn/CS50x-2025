-- Return the average energy of songs that are by Drake.

-- Requirement:
-- Don't assume Drake's artist_id and just print a single row and column that has the average energy.

-- Query:
SELECT AVG(energy) AS "Drake's Song's Average Energy" FROM songs
WHERE artist_id
= (SELECT id FROM artists WHERE name = 'Drake');
