-- Average ratings of all the movies released in the year 2012.

-- Query:
SELECT AVG(rating) AS "Average Rating of all movies released in the year 2012" FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);
