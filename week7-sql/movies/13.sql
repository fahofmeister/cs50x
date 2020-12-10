SELECT people.name
FROM people
JOIN stars ON stars.person_id=people.id
JOIN movies ON stars.movie_id=movies.id
WHERE people.name<>'Kevin Bacon' AND movies.id IN
    (SELECT stars.movie_id
    FROM stars
    INNER JOIN people ON stars.person_id=people.id
    WHERE people.name='Kevin Bacon' AND people.birth=1958);