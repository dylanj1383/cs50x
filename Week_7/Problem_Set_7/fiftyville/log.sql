-- sqlite> .tables
-- airports              crime_scene_reports   people              
-- atm_transactions      flights               phone_calls         
-- bakery_security_logs  interviews          
-- bank_accounts         passengers     

SELECT * 
FROM crime_scene_reports 
WHERE 
    year = 2024
    AND month = 7 
    AND day = 28
    AND street = 'Humphrey Street';

-- id|year|month|day|street|description
-- 295|2024|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview 
-- transcripts mentions the bakery. [X0]

-- 297|2024|7|28|Humphrey Street|Littering took place at 16:36. No known witnesses. [-]

-- [X0]
SELECT * 
FROM interviews
WHERE 
    transcript LIKE "%bakery%"
    AND year = 2024
    AND month = 7 
    AND day = 28;

-- id|name|year|month|day|transcript
-- 161|Ruth|2024|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot 
-- and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the 
-- parking lot in that time frame. [X1]

-- 162|Eugene|2024|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I 
-- arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- [X2]

-- 163|Raymond|2024|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. 
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The 
-- thief then asked the person on the other end of the phone to purchase the flight ticket. [X3]



-- [X1]
SELECT license_plate --*
FROM bakery_security_logs
WHERE 
    year = 2024 
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
    AND activity = 'exit';

-- id|year|month|day|hour|minute|activity|license_plate
-- 260|2024|7|28|10|16|exit|5P2BI95
-- 261|2024|7|28|10|18|exit|94KL13X
-- 262|2024|7|28|10|18|exit|6P58WS2
-- 263|2024|7|28|10|19|exit|4328GD8
-- 264|2024|7|28|10|20|exit|G412CB7
-- 265|2024|7|28|10|21|exit|L93JTIZ
-- 266|2024|7|28|10|23|exit|322W7JE
-- 267|2024|7|28|10|23|exit|0NTHK55

-- license_plate
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55



--[X2]
SELECT account_number --*
FROM atm_transactions
WHERE 
    year = 2024
    AND month = 7
    AND day = 28 
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street';

-- id|account_number|year|month|day|atm_location|transaction_type|amount
-- 246|28500762|2024|7|28|Leggett Street|withdraw|48
-- 264|28296815|2024|7|28|Leggett Street|withdraw|20
-- 266|76054385|2024|7|28|Leggett Street|withdraw|60
-- 267|49610011|2024|7|28|Leggett Street|withdraw|50
-- 269|16153065|2024|7|28|Leggett Street|withdraw|80
-- 288|25506511|2024|7|28|Leggett Street|withdraw|20
-- 313|81061156|2024|7|28|Leggett Street|withdraw|30
-- 336|26013199|2024|7|28|Leggett Street|withdraw|35

-- account_number
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199


--[X3]
SELECT caller --*
FROM phone_calls
WHERE 
    year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60;

-- id|caller|receiver|year|month|day|duration
-- 221|(130) 555-0289|(996) 555-8899|2024|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2024|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2024|7|28|45
-- 251|(499) 555-9472|(717) 555-1342|2024|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2024|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2024|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2024|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2024|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2024|7|28|54

-- caller
-- (130) 555-0289
-- (499) 555-9472
-- (367) 555-5533
-- (499) 555-9472
-- (286) 555-6063
-- (770) 555-1861
-- (031) 555-6622
-- (826) 555-1652
-- (338) 555-6650

-- Combine X1, X2, and X3
-- to find a person whose liscense is in X1 and whose account_number is in X2 and whose phone_number is in X3

SELECT people.id, people.name, people.passport_number

FROM people 
JOIN phone_calls 
    ON people.phone_number = phone_calls.caller
JOIN bank_accounts 
    ON bank_accounts.person_id = people.id
JOIN atm_transactions 
    ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate

WHERE 
    bakery_security_logs.year = 2024 
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25
    AND bakery_security_logs.activity = 'exit'

    AND 

    atm_transactions.year = 2024
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28 
    AND atm_transactions.transaction_type = 'withdraw'
    AND atm_transactions.atm_location = 'Leggett Street'

    AND 

    phone_calls.year = 2024
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;


-- id|name|passport_number
-- 686048|Bruce|5773159633
-- 514354|Diana|3592750733

-- lets check into both Bruce and Diana. It says the theif will be on the earliest flight tomorrow
-- lets look into flights tomorrow

SELECT * 
FROM flights 
WHERE
    year = 2024
    AND month = 7
    AND day = 29
ORDER BY hour, minute;

-- id|origin_airport_id|destination_airport_id|year|month|day|hour|minute
-- 36|8|4|2024|7|29|8|20   <-- this is the earliest flight tomorrow
-- 43|8|1|2024|7|29|9|30
-- 23|8|11|2024|7|29|12|15
-- 53|8|9|2024|7|29|15|20
-- 18|8|6|2024|7|29|16|0

SELECT * 
FROM passengers
WHERE 
    flight_id =36
    AND passport_number = 5773159633; -- bruce's passport num

-- flight_id|passport_number|seat
-- 36|5773159633|4A

SELECT * 
FROM passengers
WHERE 
    flight_id =36
    AND passport_number = 3592750733; -- Diana's passport num

-- Nothing

--THEREFORE, BRUCE IS THE THEIF

--His accomplice is who he called

SELECT name FROM people WHERE phone_number = 
(SELECT receiver
FROM phone_calls 
WHERE 
    caller =(SELECT phone_number FROM people WHERE name = 'Bruce')
    AND year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60
);

-- name
-- Robin

--THEREFORE, ROBIN IS THE ACCOMPLICE

-- The city the thief escaped to is the destination of the flight:
-- flight_id|passport_number|seat
-- 36|5773159633|4A

SELECT city FROM airports WHERE id = 
(
SELECT destination_airport_id
FROM flights
WHERE id = 36
);

-- city
-- New York City

-- THEREFORE, THE CITY HE ESCAPED TO IS NEW YORK