-- List all movies released in 2010 and their ratings, in descending order by rating.

-- For movies with the same rating, order them alphabetically by title.

-- Output: Both the title of the movie and the respective rating.
-- Movies with no rating must not be printed in the result.

-- Query:
SELECT title, rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = 2010
ORDER BY rating DESC, title ASC;
