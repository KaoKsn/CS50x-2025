-- Number of movies with a rating of 10.0

-- Query:
SELECT COUNT(*) FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0);
