-- List the titles and release years of all Harry Potter movies, in the chronological order.

-- Output: Title of the movie, year of release.
-- Assumptions: All harry potter movies start with the words 'Harry Potter'


-- Query:
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;
