-- Lists the names of songs that are by Post Malone.

-- Requirement:
--      1.Your query should output a table with a single column for the name of each song.
--      2.You should not make any assumptions about what Post Malone’s artist_id is.


-- Query:
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

