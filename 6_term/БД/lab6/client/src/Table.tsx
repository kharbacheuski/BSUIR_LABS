import React,{ Fragment }  from "react"
import { Box, Button, Typography } from "@mui/material"
import DeleteIcon from '@mui/icons-material/Delete';

const Table: React.FC<{
    rows: any[]
    setRows: React.Dispatch<React.SetStateAction<any[]>>
}> = ({rows, setRows}) => {

    const clearTable = () => {
        setRows([])
    }
    
    return <Fragment>
        <Box>
            {rows.length ? (
                    <Box sx={{display: "flex", flexDirection: "row", gap: ".5rem"}}>
                        <Typography></Typography>
                        <Box><DeleteIcon /></Box>
                    </Box>
                )
                : <Typography>Данные не найдены</Typography>
            }
        </Box>
        {rows.length ? <Button variant="contained" onClick={clearTable}>Очистить таблицу</Button> : null}
    </Fragment>
}

export default Table