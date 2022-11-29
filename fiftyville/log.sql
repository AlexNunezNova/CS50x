/* Keep a log of any SQL queries you execute as you solve the mystery.
See the schema to get an idea of the database */
.tables
.schema

--Take a look at the number of crime_scene_reports
SELECT id FROM crime_scene_reports;

-- Since they are many, select the particular crime date (or few days later) and street where they happened
SELECT id, street FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28;

-- Two crime scene reports can be found that match the info: id 295 and 297
SELECT description FROM crime_scene_reports
WHERE id IN (295, 297);

/* ID 295 gives the correct info. Hour of theft: 10.15 am at bakery:
"Theft of the CS50 duck took place at 10:15am
at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time
– each of their interview transcripts mentions the bakery. */

-- Let's look at the interviews with the matching info
SELECT id, name, transcript FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

/* IDs 160, 161 and 162 match the case:

| 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking
lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars
that left the parking lot in that time frame.                                                          |

| 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning,
before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there
withdrawing some money.
                                                                                          |
| 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less
than a minute. In the call, I heard the thief say that they were planning to take the earliest flight
out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. */

-- It is reasonable to look for the bakery footage, the ATMS and flight tickets

-- BAKERY

SELECT * FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;

/* gives the following results:
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+
which are the 8 suspect License Plates */

-- We can match that information with the People database
SELECT * FROM PEOPLE
WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25);

/* This gives the following results:
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+
Whoever matches the other information will be the thief */

/* CALLS
according to Raymond's declaration, the thief called someone to get the ticket flight */

SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

/* This is the table:
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+

now we can make the match with people's phones: */

SELECT caller, receiver FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND caller IN
    (SELECT phone_number FROM people
    WHERE license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25));

/*Which gives this result:
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (770) 555-1861 | (725) 555-3243 |
+----------------+----------------+
Therefore the suspects are reduced: */

SELECT * FROM people
WHERE phone_number IN
    (SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN
        (SELECT phone_number FROM people
        WHERE license_plate IN
            (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25)));

/* Current suspects:
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+ */

/*FLIGHTS:
Look at the bought flights the next day according to the passport number: */

--First, let's look at the earliest flight that day
SELECT DISTINCT (flights.id), flights.hour, flights.minute, airports.city, flights.destination_airport_id FROM flights
    JOIN passengers
    ON flights.id = passengers.flight_id
    JOIN people
    ON passengers.passport_number = people.passport_number
    JOIN airports
    ON airports.id = flights.origin_airport_id
WHERE year = 2021
AND month = 7
AND day = 29
ORDER BY flights.hour ASC, flights.minute ASC;

/*Results:
+----+------+--------+------------+------------------------+
| id | hour | minute |    city    | destination_airport_id |
+----+------+--------+------------+------------------------+
| 36 | 8    | 20     | Fiftyville | 4                      |
| 43 | 9    | 30     | Fiftyville | 1                      |
| 23 | 12   | 15     | Fiftyville | 11                     |
| 53 | 15   | 20     | Fiftyville | 9                      |
| 18 | 16   | 0      | Fiftyville | 6                      |
+----+------+--------+------------+------------------------+
Therefore, the earliest plane is the plane id = 36

According to the airport table:
+----+--------------+-----------------------------------------+---------------+
| id | abbreviation |                full_name                |     city      |
+----+--------------+-----------------------------------------+---------------+
| 1  | ORD          | O'Hare International Airport            | Chicago       |
| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
| 4  | LGA          | LaGuardia Airport                       | New York City |
| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
| 6  | BOS          | Logan International Airport             | Boston        |
| 7  | DXB          | Dubai International Airport             | Dubai         |
| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
| 9  | HND          | Tokyo International Airport             | Tokyo         |
| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
| 11 | SFO          | San Francisco International Airport     | San Francisco |
| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |
+----+--------------+-----------------------------------------+---------------+
The destination airport is New York City

Look at the suspect people travelling that day:*/




SELECT flights.id, people.name, passengers.passport_number FROM flights
    JOIN passengers
    ON flights.id = passengers.flight_id
    JOIN people
    ON passengers.passport_number = people.passport_number
WHERE year = 2021
AND month = 7
AND day = 29
AND passengers.passport_number IN
    (SELECT people.passport_number FROM people
    WHERE people.phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60
        AND caller IN
            (SELECT people.phone_number FROM people
            WHERE license_plate IN
                (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute BETWEEN 15 AND 25))))
AND flights.id = 36;

/* All of the current suspects are traveling the same day!.
+----+--------+-----------------+
| id |  name  | passport_number |
+----+--------+-----------------+
| 18 | Diana  | 3592750733      |
| 36 | Sofia  | 1695452385      |
| 36 | Bruce  | 5773159633      |
| 36 | Kelsey | 8294398571      |
+----+--------+-----------------+
However, Diana is discarded for not travelling on the first plane ID = 36
+----+--------+-----------------+
| id |  name  | passport_number |
+----+--------+-----------------+
| 36 | Sofia  | 1695452385      |
| 36 | Bruce  | 5773159633      |
| 36 | Kelsey | 8294398571      |
+----+--------+-----------------+

It is necessary to look at the ATM info*/

/*ATM:
According to Eugene, the thief was at the ATM on Leggett Street withdrawing some money earlier that morning */

SELECT * FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

/*
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
Match with bank accounts: */
SELECT account_number, bank_accounts.person_id, people.name, passport_number FROM bank_accounts
    JOIN people
    ON bank_accounts.person_id = people.id
WHERE account_number IN
    (SELECT account_number FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw");

/* Results:
+----------------+-----------+---------+-----------------+
| account_number | person_id |  name   | passport_number |
+----------------+-----------+---------+-----------------+
| 49610011       | 686048    | Bruce   | 5773159633      |
| 26013199       | 514354    | Diana   | 3592750733      |
| 16153065       | 458378    | Brooke  | 4408372428      |
| 28296815       | 395717    | Kenny   | 9878712108      |
| 25506511       | 396669    | Iman    | 7049073643      |
| 28500762       | 467400    | Luca    | 8496433585      |
| 76054385       | 449774    | Taylor  | 1988161715      |
| 81061156       | 438727    | Benista | 9586786673      |
+----------------+-----------+---------+-----------------+
Crossing with the previous information, we have the following: */

SELECT people.id, people.name, passengers.passport_number FROM flights
    JOIN passengers
    ON flights.id = passengers.flight_id
    JOIN people
    ON passengers.passport_number = people.passport_number
WHERE year = 2021
AND month = 7
AND day = 29
AND passengers.passport_number IN
    (SELECT people.passport_number FROM PEOPLE
    WHERE phone_number IN
        (SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60
        AND caller IN
            (SELECT phone_number FROM people
            WHERE license_plate IN
                (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute BETWEEN 15 AND 25))))
AND passengers.passport_number IN (SELECT passport_number FROM bank_accounts
    JOIN people
    ON bank_accounts.person_id = people.id
    WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"));

/* We have the following =
+--------+-------+-----------------+
|   id   | name  | passport_number |
+--------+-------+-----------------+
| 514354 | Diana | 3592750733      |
| 686048 | Bruce | 5773159633      |
+--------+-------+-----------------+
Since Diana was previously discarded because she did not travel on the first plane, the thief is Bruce! */

/* Accomplice
Bruce number is (367) 555-5533. The receiver of that call that thay was = (375) 555-8161. */

SELECT * FROM people
WHERE phone_number = "(375) 555-8161";

/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
The Accomplice is Robin! */