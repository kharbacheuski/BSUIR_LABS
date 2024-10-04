import { Box, Button, IconButton, Modal, useMediaQuery, useTheme } from "@mui/material";
import { Fragment, useContext, useState } from "react";
import menu from "./menu.json"
import LogoutIcon from '@mui/icons-material/LoginOutlined';
import type { Theme } from '@mui/material/styles/createTheme';
import MenuIcon from '@mui/icons-material/Menu';
import Paper from '@mui/material/Paper';
import CloseIcon from '@mui/icons-material/Close';
import { NavLink } from "react-router-dom";
import "./styles.scss";
import { AuthContext } from "@/providers/auth-provider";

const Navigation = () => {
    const mdUp = useMediaQuery((theme: Theme) => theme.breakpoints.down('md'));
    const { isAuth, setIsAuth } = useContext(AuthContext);

    const [isMenuOpen, setIsMenuOpen] = useState<boolean>(false)

    const handleMenu = (state: boolean = false) => {
        setIsMenuOpen(state)
    }

    const exitHandle = () => {
        handleMenu(false)
        localStorage.clear()
        setIsAuth(false)
    }

    return (
        <Fragment>
            <Box className="header_logo">
                <NavLink to="/" >
                    {/* <Logo width={60} height={60} color={theme.palette.text.primary}/> */}
                </NavLink>
            </Box>
            {!mdUp ? <Box sx={{
                display:"flex",
                flexDirection:"row",
                gap: "30px",
            }} className="header_nav">        
                {menu.map(menuItem => (
                    <NavLink
                        className={({ isActive }) => isActive ? "header_nav-link active" : "header_nav-link"}
                        key={menuItem.link}
                        to={menuItem.link}
                        onClick={() => handleMenu(false)}
                    >
                        {menuItem.name}
                    </NavLink>  
                ))}
            </Box> : <IconButton className="header_burger" onClick={() => handleMenu(true)}>
                <MenuIcon sx={{width: 30, height: 30}} />
            </IconButton>}

            {isAuth && 
                <LogoutIcon className="header_actions-logout" sx={{
                    cursor: "pointer",
                    transition: "all .1s",
                    
                    "&:hover": {
                        transform: "scale(1.1)"
                    }
                }} onClick={exitHandle} />
            }

            <Modal
                open={isMenuOpen}
                onClose={() => handleMenu(false)}
                className="header_mobile-nav" 
            >
                <Paper
                    elevation={12}
                    sx={{
                        p: "50px 20px",
                        display: 'flex',
                        flexDirection: 'column',
                        gap: "20px",
                        height: "100vh",
                        backgroundImage: "none"
                    }}
                >
                    <IconButton sx={{
                        position: "absolute",
                        top: 20,
                        right: 20
                    }} onClick={() => handleMenu(false)}>
                        <CloseIcon />
                    </IconButton>
                    <Box sx={{
                        display:"flex",
                        flexDirection:"column",
                        gap: "30px",
                    }}>        
                        {menu.map(menuItem => (
                            <NavLink
                                className={({ isActive }) => isActive ? "header_nav-link active" : "header_nav-link"}
                                key={menuItem.link}
                                to={menuItem.link}
                                onClick={() => handleMenu(false)}
                            >
                                {menuItem.name}
                            </NavLink>
                        ))}
                    </Box>
                </Paper>
            </Modal>
        </Fragment>
    )
}

export default Navigation