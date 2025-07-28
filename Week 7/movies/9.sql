-- List the names of all people who starred in a movie released in the year 2004, ordered by birth year.

-- People with the same birth year can be named in any year.
-- Output a column for each person.
-- Don't worry about people who don't have a birth year listed.
-- If a person appeared in more than a movie in the year 2005, they should only be printed once.


-- Query:
SELECT DISTINCT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT ID FROM movies WHERE year = 2004)) AND
birth IS NOT NULL
ORDER BY birth, name asc;
