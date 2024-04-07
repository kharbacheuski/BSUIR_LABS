import React,{ Fragment, useState }  from "react"
import { Button, Table, TableBody, TableCell, TableHead, TableRow } from "@mui/material"

const TableComponent: React.FC<{
    rows: any[]
    setRows: React.Dispatch<React.SetStateAction<any[]>>
}> = ({rows, setRows}) => {

    const clearTable = () => {
        setRows([])
    }

    return <Fragment>
        <Table sx={{ maxWidth: 1200 }}>
            <TableHead>
                <TableRow sx={{ '&:last-child td, &:last-child th': { border: 0 } }}>
                    {rows.length ? Object.keys(rows[0]).map((header: string, index: number) => (
                        <TableCell key={header} width={"100px"}>{header.toUpperCase()}</TableCell>
                    )) : null}
                </TableRow>
            </TableHead>
            <TableBody>
                {rows.length ? rows.map((row: any, index: number) => (
                        <TableRow key={row.id} sx={{ '&:last-child td, &:last-child th': { border: 0 } }}>
                            {Object.values(row).map(v => (
                                <TableCell key={v as string} width={"100"}>{v as string}</TableCell>
                            ))}
                        </TableRow>
                    ))
                    : <TableRow key={1}>
                        <TableCell align="center">Тут пусто</TableCell>
                    </TableRow>
                }
            </TableBody>
        </Table>

        {rows.length ? <Button variant="contained" onClick={clearTable}>Очистить таблицу</Button> : null}
    </Fragment>
}

export default TableComponent