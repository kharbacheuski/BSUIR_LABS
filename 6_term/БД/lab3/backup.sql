--
-- PostgreSQL database dump
--

-- Dumped from database version 15.0
-- Dumped by pg_dump version 16.0

-- Started on 2024-03-03 20:31:01

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 6 (class 2615 OID 16398)
-- Name: Sound-Studio; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA "Sound-Studio";


ALTER SCHEMA "Sound-Studio" OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 219 (class 1259 OID 16986)
-- Name: Artist; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Artist" (
    id integer NOT NULL,
    name character varying(200) NOT NULL,
    genre character varying(50) NOT NULL,
    "personsCount" integer NOT NULL
);


ALTER TABLE "Sound-Studio"."Artist" OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 17112)
-- Name: Artist_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Artist" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Artist_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 220 (class 1259 OID 16993)
-- Name: Employee; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Employee" (
    id integer NOT NULL,
    job character varying(50) NOT NULL,
    "workShift" integer NOT NULL,
    name character varying(100) NOT NULL
);


ALTER TABLE "Sound-Studio"."Employee" OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 17123)
-- Name: Employee_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Employee" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Employee_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 216 (class 1259 OID 16967)
-- Name: Instrument; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Instrument" (
    id integer NOT NULL,
    name character varying(50) NOT NULL,
    type character varying(50) NOT NULL,
    rent integer NOT NULL
);


ALTER TABLE "Sound-Studio"."Instrument" OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 17007)
-- Name: Instrument_Record; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Instrument_Record" (
    id integer NOT NULL,
    "Instruments_id" integer NOT NULL,
    "Record_id" integer NOT NULL
);


ALTER TABLE "Sound-Studio"."Instrument_Record" OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 17006)
-- Name: Instrument_Record_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Instrument_Record" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Instrument_Record_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 215 (class 1259 OID 16966)
-- Name: Instrument_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Instrument" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Instrument_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 222 (class 1259 OID 17001)
-- Name: Record; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Record" (
    id integer NOT NULL,
    "totalPrice" integer NOT NULL,
    "hoursCount" integer NOT NULL,
    date date NOT NULL,
    "recordTypeId" integer NOT NULL,
    "employeeId" integer NOT NULL,
    "roomId" integer NOT NULL,
    "artistId" integer NOT NULL
);


ALTER TABLE "Sound-Studio"."Record" OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 16979)
-- Name: RecordType; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."RecordType" (
    id integer NOT NULL,
    type character varying(50) NOT NULL,
    genre character varying(50),
    "stereo/mono" character varying(50) NOT NULL
);


ALTER TABLE "Sound-Studio"."RecordType" OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 17135)
-- Name: Record Type_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."RecordType" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Record Type_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 221 (class 1259 OID 17000)
-- Name: Record_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Record" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Record_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 217 (class 1259 OID 16974)
-- Name: Room; Type: TABLE; Schema: Sound-Studio; Owner: postgres
--

CREATE TABLE "Sound-Studio"."Room" (
    id integer NOT NULL,
    square integer NOT NULL,
    rent integer NOT NULL,
    "personsCount" integer NOT NULL
);


ALTER TABLE "Sound-Studio"."Room" OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 17134)
-- Name: Room_id_seq; Type: SEQUENCE; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE "Sound-Studio"."Room" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME "Sound-Studio"."Room_id_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 3382 (class 0 OID 16986)
-- Dependencies: 219
-- Data for Name: Artist; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Artist" (id, name, genre, "personsCount") FROM stdin;
1	The Smashing Pumpkins	Rock	6
2	Metallica	Metal	4
3	The Beatles	Rock	4
4	Pink Floyd	Progressive Rock	4
5	Queen	Rock	4
6	Led Zeppelin	Rock	4
7	Nirvana	Grunge	3
8	The Doors	Rock	4
9	Radiohead	Alternative Rock	5
10	AC/DC	Rock	5
11	The Who	Rock	4
12	Guns N Roses	Hard Rock	5
13	The Beach Boys	Rock	5
14	R.E.M.	Alternative Rock	4
15	The Eagles	Rock	6
16	Black Sabbath	Metal	4
17	U2	Rock	4
18	The Police	Rock	3
19	Fleetwood Mac	Rock	5
20	Deep Purple	Rock	5
21	Aerosmith	Rock	5
22	Green Day	Punk Rock	3
23	Pearl Jam	Grunge	5
24	Red Hot Chili Peppers	Alternative Rock	4
25	The Clash	Punk Rock	4
26	Blur	Alternative Rock	4
27	The Cure	Alternative Rock	4
28	Ramones	Punk Rock	4
29	Oasis	Rock	5
30	The Smiths	Indie Rock	4
\.


--
-- TOC entry 3383 (class 0 OID 16993)
-- Dependencies: 220
-- Data for Name: Employee; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Employee" (id, job, "workShift", name) FROM stdin;
1	Звукорежиссер	2	Иван Петров
2	Продюсер	1	Мария Сидорова
3	Менеджер по маркетингу	3	Алексей Иванов
4	Техник	1	Елена Козлова
5	Менеджер по продажам	2	Дмитрий Федоров
6	Звуковой дизайнер	3	Анна Николаева
7	Композитор	1	Сергей Смирнов
8	Аранжировщик	2	Ольга Павлова
9	Текстовый автор	3	Павел Кузнецов
10	Сценарист	1	Татьяна Игнатьева
11	Режиссер клипа	2	Владимир Степанов
12	Оператор	3	Максим Лебедев
13	Агент по бронированию студии	1	Евгений Романов
14	Менеджер по связям с общественностью	2	Алина Васильева
15	Программист	3	Денис Жуков
16	Дизайнер	1	Наталья Яковлева
17	Тестировщик	2	Артем Борисов
18	Контент-менеджер	3	Маргарита Калинина
19	Администратор	1	Ирина Степанова
20	Фотограф	2	Валентин Попов
21	Видеограф	3	Юлия Смирнова
22	Менеджер по контрактам	1	Андрей Кузьмин
23	Финансовый аналитик	2	Олег Михайлов
24	Юрист	3	Екатерина Волкова
25	Технический писатель	1	Полина Никитина
26	Системный администратор	2	Игорь Попов
27	HR-специалист	3	Марина Козлова
28	Логист	1	Виктор Сидоров
29	Рекрутер	2	Анна Иванова
30	Главный звукорежиссер	1	Киря Горбачевский
\.


--
-- TOC entry 3379 (class 0 OID 16967)
-- Dependencies: 216
-- Data for Name: Instrument; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Instrument" (id, name, type, rent) FROM stdin;
1	Фортепиано	Клавишные	5
2	Электрогитара	Струнные	7
3	Барабаны	Ударные	10
4	Саксофон	Духовые	8
5	Бас-гитара	Струнные	7
6	Синтезатор	Клавишные	6
7	Труба	Духовые	9
8	Контрабас	Струнные	10
9	Флейта	Духовые	8
10	Акустическая гитара	Струнные	6
11	Ударная установка	Ударные	12
12	Трубчатые колокола	Ударные	4
13	Виолончель	Струнные	9
14	Кларнет	Духовые	7
15	Тамбурин	Ударные	3
16	Электро-барабаны	Ударные	15
17	Пианино	Клавишные	7
18	Альт	Струнные	8
19	Банджо	Струнные	6
20	Микрофон	Звукозапись	4
21	Аккордеон	Клавишные	8
22	Губная гармошка	Духовые	5
23	Электронная скрипка	Струнные	10
24	Микшерный пульт	Звукозапись	10
25	DJ-пульт	Звукозапись	15
26	Семплер	Звукозапись	12
27	Акустический рояль	Клавишные	10
28	Концертный гранд-рояль	Клавишные	15
29	Электронная барабанная установка	Ударные	20
30	Электронный синтезатор	Клавишные	12
\.


--
-- TOC entry 3387 (class 0 OID 17007)
-- Dependencies: 224
-- Data for Name: Instrument_Record; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Instrument_Record" (id, "Instruments_id", "Record_id") FROM stdin;
1	1	38
2	5	56
3	12	43
4	7	54
5	2	50
6	25	33
7	9	60
8	17	45
9	29	41
10	8	59
11	4	55
12	16	53
13	20	37
14	22	46
15	11	51
16	30	48
17	6	44
18	10	52
19	18	42
20	26	47
21	3	34
22	21	58
23	15	36
24	27	35
25	19	39
26	13	61
27	14	57
28	28	49
29	24	62
30	23	40
\.


--
-- TOC entry 3385 (class 0 OID 17001)
-- Dependencies: 222
-- Data for Name: Record; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Record" (id, "totalPrice", "hoursCount", date, "recordTypeId", "employeeId", "roomId", "artistId") FROM stdin;
31	250	4	2024-02-05	57	3	11	21
32	300	3	2023-05-29	54	28	6	25
33	200	2	2023-11-18	44	30	26	1
34	350	5	2023-04-30	37	26	15	8
35	270	3	2023-07-25	53	3	18	26
36	320	4	2024-01-27	42	21	6	6
37	280	3	2024-03-01	32	7	26	18
38	400	6	2023-08-20	61	1	24	3
39	260	3	2023-05-11	48	25	21	13
40	380	5	2023-05-01	62	7	22	23
41	290	3	2023-08-29	44	7	6	29
42	250	4	2023-11-04	36	17	26	15
43	300	3	2023-10-17	58	11	26	16
44	200	2	2023-07-06	40	24	21	16
45	350	5	2023-11-10	60	28	10	14
46	270	3	2023-11-21	39	8	14	25
47	320	4	2023-11-08	49	23	18	22
48	280	3	2023-06-06	48	15	6	7
49	400	6	2023-03-14	52	4	9	27
50	260	3	2023-05-29	61	29	13	10
51	380	5	2023-10-02	60	28	21	18
52	290	3	2023-04-17	51	20	23	10
53	250	4	2023-07-30	60	14	10	18
54	300	3	2023-10-24	56	4	18	29
55	200	2	2023-06-18	39	24	19	29
56	350	5	2023-11-21	50	9	20	20
57	270	3	2023-03-07	55	22	10	13
58	320	4	2023-06-03	51	11	19	4
59	280	3	2023-04-10	62	13	1	23
60	400	6	2023-10-02	51	24	14	13
61	260	3	2023-08-05	47	16	2	28
62	380	5	2023-12-17	51	2	17	20
63	290	3	2023-03-26	50	18	9	3
\.


--
-- TOC entry 3381 (class 0 OID 16979)
-- Dependencies: 218
-- Data for Name: RecordType; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."RecordType" (id, type, genre, "stereo/mono") FROM stdin;
32	Вокал	Рок	stereo
33	Гитара	Рок	mono
34	Барабаны	Рок	stereo
35	Клавишные	Рок	mono
36	Бас-гитара	Рок	stereo
37	Скрипка	Классика	stereo
38	Фортепиано	Классика	mono
39	Смычковые	Классика	stereo
40	Духовые	Джаз	mono
41	Контрабас	Джаз	stereo
42	Труба	Джаз	stereo
43	Тенор-саксофон	Джаз	mono
44	Флейта	Классика	stereo
45	Акустическая гитара	Фолк	stereo
46	Банджо	Фолк	mono
47	Мандолина	Фолк	stereo
48	Скрипка	Фолк	mono
49	Акустическая гитара	Акустика	stereo
50	Виолончель	Классика	mono
51	Концертный рояль	Классика	stereo
52	Вокал	Поп	stereo
53	Гитара	Поп	mono
54	Клавишные	Поп	stereo
55	Бас-гитара	Поп	stereo
56	Электронные	Электроника	stereo
57	Синтезатор	Электроника	mono
58	Сэмплер	Электроника	stereo
59	Скрэтч	Хип-хоп	mono
60	Вокал	Хип-хоп	stereo
61	Бас-гитара	Хип-хоп	stereo
62	Ударные	Хип-хоп	mono
\.


--
-- TOC entry 3380 (class 0 OID 16974)
-- Dependencies: 217
-- Data for Name: Room; Type: TABLE DATA; Schema: Sound-Studio; Owner: postgres
--

COPY "Sound-Studio"."Room" (id, square, rent, "personsCount") FROM stdin;
1	25	12	4
2	30	15	6
3	20	10	3
4	35	18	8
5	28	14	5
6	22	11	4
7	32	16	7
8	27	13	5
9	18	9	3
10	40	20	10
11	26	14	6
12	23	12	4
13	38	18	9
14	21	11	3
15	29	15	7
16	34	17	8
17	31	16	6
18	24	12	5
19	37	19	9
20	19	10	4
21	36	18	8
22	33	17	7
23	25	13	5
24	20	10	4
25	30	15	7
26	28	14	6
27	22	12	5
28	35	18	9
29	27	13	6
30	23	11	4
\.


--
-- TOC entry 3397 (class 0 OID 0)
-- Dependencies: 225
-- Name: Artist_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Artist_id_seq"', 30, true);


--
-- TOC entry 3398 (class 0 OID 0)
-- Dependencies: 226
-- Name: Employee_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Employee_id_seq"', 30, true);


--
-- TOC entry 3399 (class 0 OID 0)
-- Dependencies: 223
-- Name: Instrument_Record_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Instrument_Record_id_seq"', 30, true);


--
-- TOC entry 3400 (class 0 OID 0)
-- Dependencies: 215
-- Name: Instrument_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Instrument_id_seq"', 30, true);


--
-- TOC entry 3401 (class 0 OID 0)
-- Dependencies: 228
-- Name: Record Type_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Record Type_id_seq"', 62, true);


--
-- TOC entry 3402 (class 0 OID 0)
-- Dependencies: 221
-- Name: Record_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Record_id_seq"', 63, true);


--
-- TOC entry 3403 (class 0 OID 0)
-- Dependencies: 227
-- Name: Room_id_seq; Type: SEQUENCE SET; Schema: Sound-Studio; Owner: postgres
--

SELECT pg_catalog.setval('"Sound-Studio"."Room_id_seq"', 30, true);


--
-- TOC entry 3211 (class 2606 OID 16992)
-- Name: Artist Artist_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Artist"
    ADD CONSTRAINT "Artist_pkey" PRIMARY KEY (id);


--
-- TOC entry 3213 (class 2606 OID 16999)
-- Name: Employee Employee_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Employee"
    ADD CONSTRAINT "Employee_pkey" PRIMARY KEY (id);


--
-- TOC entry 3217 (class 2606 OID 17011)
-- Name: Instrument_Record Instrument_Record_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_pkey" PRIMARY KEY (id);


--
-- TOC entry 3205 (class 2606 OID 16973)
-- Name: Instrument Instrument_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument"
    ADD CONSTRAINT "Instrument_pkey" PRIMARY KEY (id);


--
-- TOC entry 3209 (class 2606 OID 16985)
-- Name: RecordType Record Type_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."RecordType"
    ADD CONSTRAINT "Record Type_pkey" PRIMARY KEY (id);


--
-- TOC entry 3215 (class 2606 OID 17005)
-- Name: Record Record_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_pkey" PRIMARY KEY (id);


--
-- TOC entry 3207 (class 2606 OID 16978)
-- Name: Room Room_pkey; Type: CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Room"
    ADD CONSTRAINT "Room_pkey" PRIMARY KEY (id);


--
-- TOC entry 3230 (class 2606 OID 17032)
-- Name: Instrument_Record Instrument_Record_Instruments_id_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Instruments_id_fkey" FOREIGN KEY ("Instruments_id") REFERENCES "Sound-Studio"."Instrument"(id) NOT VALID;


--
-- TOC entry 3231 (class 2606 OID 17062)
-- Name: Instrument_Record Instrument_Record_Instruments_id_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Instruments_id_fkey1" FOREIGN KEY ("Instruments_id") REFERENCES "Sound-Studio"."Instrument"(id) NOT VALID;


--
-- TOC entry 3232 (class 2606 OID 17092)
-- Name: Instrument_Record Instrument_Record_Instruments_id_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Instruments_id_fkey2" FOREIGN KEY ("Instruments_id") REFERENCES "Sound-Studio"."Instrument"(id) NOT VALID;


--
-- TOC entry 3233 (class 2606 OID 17037)
-- Name: Instrument_Record Instrument_Record_Record_id_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Record_id_fkey" FOREIGN KEY ("Record_id") REFERENCES "Sound-Studio"."Record"(id) NOT VALID;


--
-- TOC entry 3234 (class 2606 OID 17067)
-- Name: Instrument_Record Instrument_Record_Record_id_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Record_id_fkey1" FOREIGN KEY ("Record_id") REFERENCES "Sound-Studio"."Record"(id) NOT VALID;


--
-- TOC entry 3235 (class 2606 OID 17097)
-- Name: Instrument_Record Instrument_Record_Record_id_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Instrument_Record"
    ADD CONSTRAINT "Instrument_Record_Record_id_fkey2" FOREIGN KEY ("Record_id") REFERENCES "Sound-Studio"."Record"(id) NOT VALID;


--
-- TOC entry 3218 (class 2606 OID 17022)
-- Name: Record Record_artistId_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_artistId_fkey" FOREIGN KEY ("artistId") REFERENCES "Sound-Studio"."Artist"(id) NOT VALID;


--
-- TOC entry 3219 (class 2606 OID 17052)
-- Name: Record Record_artistId_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_artistId_fkey1" FOREIGN KEY ("artistId") REFERENCES "Sound-Studio"."Artist"(id) NOT VALID;


--
-- TOC entry 3220 (class 2606 OID 17082)
-- Name: Record Record_artistId_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_artistId_fkey2" FOREIGN KEY ("artistId") REFERENCES "Sound-Studio"."Artist"(id) NOT VALID;


--
-- TOC entry 3221 (class 2606 OID 17017)
-- Name: Record Record_employeeId_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_employeeId_fkey" FOREIGN KEY ("employeeId") REFERENCES "Sound-Studio"."Employee"(id) NOT VALID;


--
-- TOC entry 3222 (class 2606 OID 17047)
-- Name: Record Record_employeeId_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_employeeId_fkey1" FOREIGN KEY ("employeeId") REFERENCES "Sound-Studio"."Employee"(id) NOT VALID;


--
-- TOC entry 3223 (class 2606 OID 17077)
-- Name: Record Record_employeeId_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_employeeId_fkey2" FOREIGN KEY ("employeeId") REFERENCES "Sound-Studio"."Employee"(id) NOT VALID;


--
-- TOC entry 3224 (class 2606 OID 17012)
-- Name: Record Record_recordTypeId_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_recordTypeId_fkey" FOREIGN KEY ("recordTypeId") REFERENCES "Sound-Studio"."RecordType"(id) NOT VALID;


--
-- TOC entry 3225 (class 2606 OID 17042)
-- Name: Record Record_recordTypeId_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_recordTypeId_fkey1" FOREIGN KEY ("recordTypeId") REFERENCES "Sound-Studio"."RecordType"(id) NOT VALID;


--
-- TOC entry 3226 (class 2606 OID 17072)
-- Name: Record Record_recordTypeId_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_recordTypeId_fkey2" FOREIGN KEY ("recordTypeId") REFERENCES "Sound-Studio"."RecordType"(id) NOT VALID;


--
-- TOC entry 3227 (class 2606 OID 17027)
-- Name: Record Record_roomId_fkey; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_roomId_fkey" FOREIGN KEY ("roomId") REFERENCES "Sound-Studio"."Room"(id) NOT VALID;


--
-- TOC entry 3228 (class 2606 OID 17057)
-- Name: Record Record_roomId_fkey1; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_roomId_fkey1" FOREIGN KEY ("roomId") REFERENCES "Sound-Studio"."Room"(id) NOT VALID;


--
-- TOC entry 3229 (class 2606 OID 17087)
-- Name: Record Record_roomId_fkey2; Type: FK CONSTRAINT; Schema: Sound-Studio; Owner: postgres
--

ALTER TABLE ONLY "Sound-Studio"."Record"
    ADD CONSTRAINT "Record_roomId_fkey2" FOREIGN KEY ("roomId") REFERENCES "Sound-Studio"."Room"(id) NOT VALID;


-- Completed on 2024-03-03 20:31:02

--
-- PostgreSQL database dump complete
--

