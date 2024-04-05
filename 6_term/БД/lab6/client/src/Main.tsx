import { Box } from "@mui/material"
import Table from "./Table"
import Form from "./Form"
import Info from "./Info"
import { useState } from "react"
import "./base.css"

const Main = () => {
	const [rows, setRows] = useState<any[]>([]);

  	return (
		<Box sx={{display: "flex", gap: "5rem", flexDirection: "column", alignItems: "center"}}>
			<Info />
			<Form setRows={setRows} />
			<Table rows={rows} setRows={setRows}/>
		</Box>
	);
}

export default Main;
