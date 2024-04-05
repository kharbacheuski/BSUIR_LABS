import axios from "axios";

const api = axios.create({
    baseURL: "http://localhost:5000/api",
    headers: {
        ['Content-Type']: "application/json; charset=utf8"
    }
});

export const endpoints = {
    1: "where",
    2: "where-orderBy",
    3: "orderBy",
    4: "select",
    5: "select-where",
    6: "crossJoin",
    7: "crossJoin-2",
    8: "innerJoin",
    9: "innerJoin-where",
    10: "leftOuterJoin-where",
    11: "leftOuterJoin",
    12: "rightOuterJoin",
    13: "rightOuterJoin-2",
    14: "fullOuterJoin",
    15: "fullOuterJoin-2",

    16: "count",
    17: "count-distinct",
    18: "max",
    19: "max-2",
    20: "sum",
    21: "sum-distinct",
    22: "groupBy",
    23: "groupBy-having",
    24: "having-avg",
    25: "union-not",
    26: "union-any",
    27: "intersect",
    28: "intersect-where",
    29: "except-exists",
    30: "except-all",
}

export const query = (number: number) => api.get<any>(`/${endpoints[number]}/`)
