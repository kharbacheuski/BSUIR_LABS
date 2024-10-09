--
-- PostgreSQL database dump
--

-- Dumped from database version 17.0
-- Dumped by pg_dump version 17.0

-- Started on 2024-10-09 10:46:06

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 217 (class 1259 OID 16424)
-- Name: genre; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genre (
    id integer NOT NULL,
    name character varying,
    instruments character varying
);


ALTER TABLE public.genre OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 16429)
-- Name: genre_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.genre ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.genre_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 219 (class 1259 OID 16430)
-- Name: group; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."group" (
    id integer NOT NULL,
    name character varying,
    "personsCount" integer,
    popularity integer
);


ALTER TABLE public."group" OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16435)
-- Name: group_genre; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.group_genre (
    id integer NOT NULL,
    "groupId" integer,
    "genreId" integer
);


ALTER TABLE public.group_genre OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16438)
-- Name: group_genre_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.group_genre ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.group_genre_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 222 (class 1259 OID 16439)
-- Name: group_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public."group" ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.group_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 223 (class 1259 OID 16440)
-- Name: record; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.record (
    id integer NOT NULL,
    number character varying,
    date date,
    hours integer,
    "roomId" integer,
    "groupId" integer
);


ALTER TABLE public.record OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 16445)
-- Name: record_genre; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.record_genre (
    id integer NOT NULL,
    "recordId" integer,
    "genreId" integer
);


ALTER TABLE public.record_genre OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 16448)
-- Name: record_genre_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.record_genre ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.record_genre_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 226 (class 1259 OID 16449)
-- Name: record_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.record ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.record_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 227 (class 1259 OID 16450)
-- Name: room; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.room (
    id integer NOT NULL,
    number character varying,
    square integer,
    "personsCount" integer,
    rent numeric
);


ALTER TABLE public.room OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 16455)
-- Name: room_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.room ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.room_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 4829 (class 0 OID 16424)
-- Dependencies: 217
-- Data for Name: genre; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genre (id, name, instruments) FROM stdin;
1	Rock	solo-guitar, drums
2	Blues	guitar, piano
3	Rock	guitar, bass, drums
4	Jazz	saxophone, piano, double bass, drums
5	Classical	violin, cello, piano, flute
6	Pop	synthesizer, guitar, bass, drums
7	Hip Hop	turntables, drum machine, synthesizer, sampler
8	Blues	guitar, harmonica, bass, drums
9	Country	guitar, banjo, fiddle, bass
10	Reggae	guitar, bass, drums, keyboard
11	Electronic	synthesizer, drum machine, sequencer
12	Folk	guitar, banjo, mandolin, violin
13	Metal	electric guitar, bass, drums, vocals
14	Punk	electric guitar, bass, drums
15	Disco	synthesizer, bass, drums, guitar
16	Funk	bass, drums, guitar, keyboard
17	Soul	guitar, bass, piano, drums
18	R&B	guitar, bass, piano, drums
19	Gospel	organ, piano, drums, guitar
20	Ska	trumpet, saxophone, trombone, guitar, drums
21	House	synthesizer, drum machine, sequencer
22	Techno	synthesizer, drum machine, sequencer
23	Trance	synthesizer, drum machine, sequencer
24	Dubstep	synthesizer, drum machine, sampler
25	Drum and Bass	drum machine, sampler, synthesizer
26	Ambient	synthesizer, piano, guitar
27	Industrial	guitar, synthesizer, drum machine
28	Grunge	guitar, bass, drums
29	Alternative Rock	guitar, bass, drums, keyboard
30	Post-Rock	guitar, bass, drums, keyboard
31	Progressive Rock	guitar, bass, drums, keyboard
32	Experimental	synthesizer, guitar, bass, various
33	New Wave	synthesizer, guitar, bass, drums
34	Synthpop	synthesizer, drum machine, sequencer
35	Electro	synthesizer, drum machine, sequencer
36	Hardcore	guitar, bass, drums, vocals
37	Post-Punk	guitar, bass, drums, synthesizer
38	Shoegaze	guitar, bass, drums, synthesizer
39	Indie Rock	guitar, bass, drums, keyboard
40	Indie Pop	guitar, bass, drums, synthesizer
41	Lo-fi	guitar, bass, drums, synthesizer
42	Emo	guitar, bass, drums, vocals
43	Math Rock	guitar, bass, drums, keyboard
44	Post-Metal	guitar, bass, drums, keyboard
45	Black Metal	guitar, bass, drums, vocals
46	Death Metal	guitar, bass, drums, vocals
47	Doom Metal	guitar, bass, drums, vocals
48	Sludge Metal	guitar, bass, drums, vocals
49	Thrash Metal	guitar, bass, drums, vocals
50	Hard Rock	guitar, bass, drums, vocals
51	Psychedelic Rock	guitar, bass, drums, keyboard
52	Progressive Metal	guitar, bass, drums, keyboard
\.


--
-- TOC entry 4831 (class 0 OID 16430)
-- Dependencies: 219
-- Data for Name: group; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."group" (id, name, "personsCount", popularity) FROM stdin;
1	Metallica	4	80
2	Nirvana	3	100
3	The Beatles	4	100
4	Queen	4	95
5	Led Zeppelin	4	93
6	Pink Floyd	4	92
7	The Rolling Stones	5	94
8	Metallica	4	90
9	Nirvana	3	89
10	Radiohead	5	85
11	Coldplay	4	88
12	Red Hot Chili Peppers	4	86
13	U2	4	87
14	The Doors	4	84
15	Guns N Roses	5	83
16	AC/DC	5	91
17	Linkin Park	6	82
18	The Who	4	85
19	Deep Purple	5	80
20	The Eagles	5	81
21	Rammstein	6	78
22	Muse	3	79
23	The Killers	4	77
24	Foo Fighters	5	76
25	The Strokes	5	74
26	Imagine Dragons	4	75
27	Green Day	3	88
28	Blink-182	3	70
29	The White Stripes	2	69
30	Oasis	5	73
31	Arctic Monkeys	4	72
32	Tame Impala	1	68
33	The Black Keys	2	66
34	Pearl Jam	5	78
35	The Smashing Pumpkins	4	67
36	Korn	5	65
37	Slipknot	9	64
38	Bon Jovi	5	71
39	Fleetwood Mac	5	83
40	The Kinks	4	63
41	Depeche Mode	3	75
42	Joy Division	4	62
43	The Smiths	4	74
44	The Clash	4	76
45	Sex Pistols	4	61
46	Ramones	4	73
47	Beastie Boys	3	70
48	The Cure	5	72
49	Talking Heads	4	68
50	Pulp	5	66
51	Arcade Fire	6	77
\.


--
-- TOC entry 4832 (class 0 OID 16435)
-- Dependencies: 220
-- Data for Name: group_genre; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.group_genre (id, "groupId", "genreId") FROM stdin;
1	1	1
5	1	1
6	1	5
7	1	13
8	2	1
9	2	29
10	2	14
11	3	1
12	3	30
13	3	11
14	4	1
15	4	29
16	4	28
17	5	1
18	5	14
19	5	6
20	6	11
21	6	47
22	6	1
23	7	1
24	7	26
25	7	12
26	8	1
27	8	29
28	8	27
29	9	4
30	9	1
31	9	10
32	10	1
33	10	14
34	10	2
35	11	1
36	11	10
37	11	4
38	12	1
39	12	6
40	12	11
41	13	1
42	13	11
43	13	6
44	14	11
45	14	1
46	14	48
47	15	36
48	15	37
49	15	47
50	16	1
51	16	29
52	16	14
53	17	1
54	17	11
55	17	48
56	18	1
57	18	10
58	18	4
59	19	11
60	19	25
61	19	47
62	20	1
63	20	29
64	20	36
65	21	1
66	21	4
67	21	38
68	22	1
69	22	12
70	22	27
71	23	27
72	23	38
73	23	1
74	24	1
75	24	4
76	24	9
77	25	1
78	25	12
79	25	34
80	26	12
81	26	34
82	26	1
83	27	1
84	27	39
85	27	10
86	28	27
87	28	1
88	28	4
89	29	38
90	29	27
91	29	1
92	30	30
93	30	9
94	30	28
95	31	1
96	31	6
97	31	10
98	32	1
99	32	27
100	32	26
101	33	26
102	33	27
103	33	29
104	34	11
105	34	42
106	34	47
107	35	11
108	35	47
109	35	42
110	36	11
111	36	48
112	36	1
113	37	1
114	37	10
115	37	4
116	38	1
117	38	6
118	38	14
119	39	38
120	39	9
121	39	33
122	40	27
123	40	9
124	40	35
125	41	27
126	41	38
127	41	35
128	42	12
129	42	34
130	42	1
131	43	12
132	43	34
133	43	1
134	44	12
135	44	34
136	44	1
137	45	1
138	45	5
139	45	12
140	46	1
141	46	35
142	46	28
143	47	29
144	47	1
145	47	30
146	48	38
147	48	1
\.


--
-- TOC entry 4835 (class 0 OID 16440)
-- Dependencies: 223
-- Data for Name: record; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.record (id, number, date, hours, "roomId", "groupId") FROM stdin;
1	asd123	2024-12-05	123	2	1
2	1	2024-09-20	2	1	5
3	2	2024-08-15	3	2	12
4	3	2024-07-10	1	3	8
5	4	2024-06-25	4	1	15
6	5	2024-10-05	2	2	3
7	6	2024-09-01	3	3	20
8	7	2024-05-18	1	1	7
9	8	2024-04-22	4	2	17
10	9	2024-03-19	2	3	1
11	10	2024-10-10	3	1	10
12	11	2024-02-27	1	2	4
13	12	2024-01-15	2	3	19
14	13	2024-05-05	4	1	13
15	14	2024-06-14	3	2	9
16	15	2024-07-07	2	3	11
17	16	2024-08-29	1	1	6
18	17	2024-09-13	2	2	14
19	18	2024-04-03	4	3	2
20	19	2024-10-01	3	1	18
21	20	2024-09-15	1	2	16
\.


--
-- TOC entry 4836 (class 0 OID 16445)
-- Dependencies: 224
-- Data for Name: record_genre; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.record_genre (id, "recordId", "genreId") FROM stdin;
1	1	1
2	1	5
3	2	11
4	2	12
5	2	47
6	3	1
7	3	27
8	4	1
9	4	29
10	4	14
11	5	6
12	5	1
13	6	11
14	6	47
15	7	1
16	7	10
17	7	6
18	8	14
19	8	1
20	9	12
21	9	34
22	10	1
23	10	29
24	10	28
25	11	12
26	11	1
27	12	4
28	12	38
29	13	27
30	13	29
31	14	1
32	14	6
33	15	1
34	15	5
35	16	12
36	16	34
37	17	1
38	17	47
39	18	9
40	18	30
41	19	1
42	19	29
43	20	38
44	20	27
\.


--
-- TOC entry 4839 (class 0 OID 16450)
-- Dependencies: 227
-- Data for Name: room; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.room (id, number, square, "personsCount", rent) FROM stdin;
1	510	50	25	12.5
2	207-4	50	25	957
3	105-A	150	8	50
\.


--
-- TOC entry 4846 (class 0 OID 0)
-- Dependencies: 218
-- Name: genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.genre_id_seq', 52, true);


--
-- TOC entry 4847 (class 0 OID 0)
-- Dependencies: 221
-- Name: group_genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.group_genre_id_seq', 147, true);


--
-- TOC entry 4848 (class 0 OID 0)
-- Dependencies: 222
-- Name: group_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.group_id_seq', 51, true);


--
-- TOC entry 4849 (class 0 OID 0)
-- Dependencies: 225
-- Name: record_genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.record_genre_id_seq', 44, true);


--
-- TOC entry 4850 (class 0 OID 0)
-- Dependencies: 226
-- Name: record_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.record_id_seq', 21, true);


--
-- TOC entry 4851 (class 0 OID 0)
-- Dependencies: 228
-- Name: room_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.room_id_seq', 3, true);


--
-- TOC entry 4667 (class 2606 OID 16457)
-- Name: genre genre_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genre
    ADD CONSTRAINT genre_pkey PRIMARY KEY (id);


--
-- TOC entry 4671 (class 2606 OID 16459)
-- Name: group_genre group_genre_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.group_genre
    ADD CONSTRAINT group_genre_pkey PRIMARY KEY (id);


--
-- TOC entry 4669 (class 2606 OID 16461)
-- Name: group group_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."group"
    ADD CONSTRAINT group_pkey PRIMARY KEY (id);


--
-- TOC entry 4675 (class 2606 OID 16463)
-- Name: record_genre record_genre_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record_genre
    ADD CONSTRAINT record_genre_pkey PRIMARY KEY (id);


--
-- TOC entry 4673 (class 2606 OID 16465)
-- Name: record record_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record
    ADD CONSTRAINT record_pkey PRIMARY KEY (id);


--
-- TOC entry 4677 (class 2606 OID 16467)
-- Name: room room_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.room
    ADD CONSTRAINT room_pkey PRIMARY KEY (id);


--
-- TOC entry 4678 (class 2606 OID 16468)
-- Name: group_genre group_genre_genre; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.group_genre
    ADD CONSTRAINT group_genre_genre FOREIGN KEY ("genreId") REFERENCES public.genre(id);


--
-- TOC entry 4679 (class 2606 OID 16473)
-- Name: group_genre group_genre_group; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.group_genre
    ADD CONSTRAINT group_genre_group FOREIGN KEY ("groupId") REFERENCES public."group"(id);


--
-- TOC entry 4682 (class 2606 OID 16478)
-- Name: record_genre record_genre_genre; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record_genre
    ADD CONSTRAINT record_genre_genre FOREIGN KEY ("genreId") REFERENCES public.genre(id);


--
-- TOC entry 4683 (class 2606 OID 16483)
-- Name: record_genre record_genre_record; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record_genre
    ADD CONSTRAINT record_genre_record FOREIGN KEY ("recordId") REFERENCES public.record(id);


--
-- TOC entry 4680 (class 2606 OID 16488)
-- Name: record record_group; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record
    ADD CONSTRAINT record_group FOREIGN KEY ("groupId") REFERENCES public."group"(id) NOT VALID;


--
-- TOC entry 4681 (class 2606 OID 16493)
-- Name: record record_room; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.record
    ADD CONSTRAINT record_room FOREIGN KEY ("roomId") REFERENCES public.room(id) NOT VALID;


-- Completed on 2024-10-09 10:46:06

--
-- PostgreSQL database dump complete
--

