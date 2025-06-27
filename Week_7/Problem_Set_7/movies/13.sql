-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

SELECT people.name FROM people WHERE people.id IN 
(
SELECT stars.person_id FROm stars WHERE stars.movie_id IN 
(
SELECT stars.movie_id FROM stars WHERE stars.person_id = 
(SELECT id FROM people WHERE name = 'Kevin Bacon')
)

)
AND people.name != 'Kevin Bacon';