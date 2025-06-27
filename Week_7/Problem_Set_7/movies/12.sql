-- In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Bradley Cooper.
-- You may assume that there is only one person in the database with the name Jennifer Lawrence.
SELECT title FROM movies WHERE id IN
(
SELECT movie_id
FROM stars
WHERE stars.person_id = 
(SELECT people.id FROM people WHERE people.name = 'Bradley Cooper') 
AND movie_id IN 

(
SELECT movie_id
FROM stars
WHERE stars.person_id = 
(SELECT people.id FROM people WHERE people.name = 'Jennifer Lawrence')
)-- this contains all movie_ids for jen 
);