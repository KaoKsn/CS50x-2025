-- Lists the names of the songs that feature other artists

-- Requirement:
--      1.Your query must ouput only the name of the songs that contain: "feat." in their name.

-- Query:
SELECT name FROM songs WHERE name LIKE '%feat.%';
