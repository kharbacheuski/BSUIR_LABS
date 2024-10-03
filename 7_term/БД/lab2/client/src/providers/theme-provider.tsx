import React, { useEffect, createContext, useState, useMemo } from 'react';
import { ThemeProvider as MuiThemeProvider, CssBaseline } from "@mui/material"
import {theme} from '../utilities/theme';

type ThemeContextType = {
    isThemeDark: boolean,
    setIsThemeDark:  React.Dispatch<React.SetStateAction<boolean>>
}

export const ThemeContext = createContext<ThemeContextType>({
    isThemeDark: false,
    setIsThemeDark: () => {}
})

declare module "@mui/material/styles" {
    interface Palette {
        header: string
        currency: string
    }
    interface PaletteOptions {
        header: string;
        currency: string
    }
}
 
function ThemeProvider({ children }) {
    const [isThemeDark, setIsThemeDark] = useState<boolean>(false)

    useEffect(() => {
        setIsThemeDark(localStorage.getItem('theme') == "dark")
    }, [])

    const themeState = useMemo(() => theme(isThemeDark), [isThemeDark])

    return (
        <ThemeContext.Provider value={{isThemeDark, setIsThemeDark}}>
            <MuiThemeProvider theme={themeState}>
                <CssBaseline />
                {children}
            </MuiThemeProvider>
        </ThemeContext.Provider>
    )
}

export default ThemeProvider