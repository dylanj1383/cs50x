-- SELECT name FROM people WHERE id in 
-- (SELECT person_id FROM stars WHERE movie_id in
-- (SELECT movie_id FROM movies WHERE year = 2004))
-- ORDER BY birth; 
-- ^ this is inifficient

SELECT DISTINCT people.name 
FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id
WHERE year = 2004
ORDER BY people.birth;