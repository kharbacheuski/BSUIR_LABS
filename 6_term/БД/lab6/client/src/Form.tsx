<<<<<<< HEAD
import React, {Fragment, useState} from "react"
import { Button, Box, Typography, TextField } from "@mui/material"
import { queryGet, queryDelete, queryUpdate, queryInsert } from "./api/endpoints"
=======
import React, {useState} from "react"
import { Button, Box, Typography, TextField } from "@mui/material"
import { query } from "./api/endpoints"
>>>>>>> 11361593a0c50db0b14e68c8d87d9bd2d6b55aa7

const Form: React.FC<{
    setRows: React.Dispatch<React.SetStateAction<any[]>>
}> = ({setRows}) => {

    const [queryNumber, setQueryNumber] = useState<number | null>(null)
    const [table, setTable] = useState<string>("")
    const [id, setId] = useState<number>(0)

    const [columns, setColumns] = useState<any[]>([])

    const handleClick = async (e: any, type = "get") => {
        try {
            let data;
            switch (type) {
                case "get": data = (await queryGet(queryNumber!, {table, id})).data; break
                case "delete": data = (await queryDelete(queryNumber!, {table, id})).data; break
                case "update": data = (await queryUpdate(queryNumber!, {table, id})).data; break
            }


            setRows(data)
        }
        catch (e) {
            console.error(e)
        }
    }

<<<<<<< HEAD
    return <Fragment>
        <Box sx={{display: "flex", flexDirection: "column", gap: "30px", width: "350px"}}>
            <TextField type="number" value={queryNumber} onChange={(e) => setQueryNumber(Number(e.target.value))} placeholder="Введите номер запроса" />
            <TextField type="text" value={table} onChange={(e) => setTable(e.target.value)} placeholder="Введите таблицу" />
            <TextField type="number" value={id} onChange={(e) => setId(Number(e.target.value))} placeholder="Введите id записи" />

            <Box sx={{display: "flex", gap: "10px"}}>
                <Button variant="contained" onClick={(e) => handleClick(e, "get")}>Получить результат</Button>
                <Button color="error" variant="contained" onClick={(e) => handleClick(e, "delete")}>Удалить запись</Button>
            </Box>
        </Box>

        {/* <Box sx={{display: "flex", flexDirection: "column", gap: "30px", width: "350px"}}>
            <TextField type="text" value={columns["1"]} onChange={(e) => setColumns({...columns, 1: e.target.value})} placeholder="Поле 1" />
            <TextField type="text" value={columns["2"]} onChange={(e) => setColumns({...columns, 3: e.target.value})} placeholder="Поле 2" />
            <TextField type="text" value={columns["3"]} onChange={(e) => setColumns({...columns, 2: e.target.value})} placeholder="Поле 3" />

            <Box sx={{display: "flex", gap: "10px"}}>
                <Button variant="contained" onClick={(e) => handleClick(e, "create")}>Создать запись</Button>
                <Button color="error" variant="contained" onClick={(e) => handleClick(e, "update")}>Обновить запись</Button>
            </Box>
        </Box> */}
    </Fragment>
=======
    return (
        <Box sx={{display: "flex", flexDirection: "column", gap: "30px", width: "350px"}}>
            <TextField type="number" value={queryNumber} onChange={(e) => setQueryNumber(Number(e.target.value))} placeholder="Введите номер запроса" />
            <Button variant="contained" onClick={handleClick}>Получить результат</Button>
        </Box>
    )
>>>>>>> 11361593a0c50db0b14e68c8d87d9bd2d6b55aa7
}

export default Form