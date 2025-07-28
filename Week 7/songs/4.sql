-- List the names of any songs that have danceability, energy, and valence greater than 0.75.

-- Requirement: Just output the name of the song.

-- Query:
SELECT name FROM songs WHERE (danceability > 0.75 AND energy > 0.75 AND valence > 0.75);
