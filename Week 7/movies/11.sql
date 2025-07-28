-- List the titles of the five highest rated movies (in order) that Chadwick Boseman starred in,
-- starting with the highest rated.

-- Just list the title of each movie.
-- Assume that there is only one person by the name 'Chadwick Boseman' in the database.

-- Query:
SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE movies.id IN
(SELECT movie_id FROM stars
WHERE person_id = (SELECT id FROM people WHERE name = 'Chadwick Boseman')
) ORDER BY rating DESC
LIMIT 5;
