import React, {useState} from "react"
import { Button, Box, Typography, TextField } from "@mui/material"
import { query } from "./api/endpoints"

const Form: React.FC<{
    setRows: React.Dispatch<React.SetStateAction<any[]>>
}> = ({setRows}) => {

    const [queryNumber, setQueryNumber] = useState<number | null>(null)

    const handleClick = async (e: any) => {
        try {
            const {data} = await query(queryNumber!)

            setRows(data)
        }
        catch (e) {
            console.error(e)
        }
    }

    return (
        <Box sx={{display: "flex", flexDirection: "column", gap: "30px", width: "350px"}}>
            <TextField type="number" value={queryNumber} onChange={(e) => setQueryNumber(Number(e.target.value))} placeholder="Введите номер запроса" />
            <Button variant="contained" onClick={handleClick}>Получить результат</Button>
        </Box>
    )
}

export default Form