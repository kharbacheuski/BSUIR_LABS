import { Box, useMediaQuery } from "@mui/material";
import type { Theme } from '@mui/material/styles/createTheme';
import Navigation from "./Navigation";
import { useNavigate } from "react-router-dom";
import { useContext } from "react";
import { AuthContext } from "@/providers/auth-provider";

const Header = () => {
    const {isAuth} = useContext(AuthContext)

    return isAuth && (
        <Box component={"header"} sx={(theme) => ({
            width: "100%",
            padding: "15px 20px",
            display: "flex",                   
            justifyContent: "space-between",
            alignItems:"center",    
            // backgroundColor: theme.palette.header,
            backdropFilter: "saturate(180%) blur(10px)",
            position: "sticky",
            top: 0,
            zIndex: 10,
        })} className="page_header header">
            <Navigation />
        </Box>
    )
}

export default Header