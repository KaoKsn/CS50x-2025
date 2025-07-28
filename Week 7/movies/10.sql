-- List the names of all people who have directed a movie that received a rating of alteast 9.0

-- If a director directed more than one movies which rate >= 9.0 , print them only once.

-- Query:
SELECT DISTINCT name FROM people WHERE id IN
(SELECT person_id FROM directors WHERE movie_id IN
(SELECT movie_id FROM ratings where rating >= 9.0)
) ORDER BY name ASC;
