SELECT DISTINCT people.name
FROM movies JOIN directors ON movies.id = directors.movie_id
JOIN people ON people.id = directors.person_id
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating >= 9.0;