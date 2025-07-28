-- List the titles of all movies in which both Bradley Cooper and Jennifer Lawrenece starred.

-- You can assume that the names 'Bradley Cooper' and 'Jennifer Lawrenece' are unique in the database.

-- Query:
SELECT title FROM movies WHERE
id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence'))
AND
id IN (SELECt movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper'));


-- To list movies where either of them starred.
-- select title from movies where id in (select movie_id from stars where person_id in (select id from people where name = 'Jennifer Lawrence' or name = 'Bradley Cooper'))
