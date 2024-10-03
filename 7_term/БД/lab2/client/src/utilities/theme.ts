import { Shadows, createTheme } from '@mui/material/styles';

export const theme = (isThemeDark) => createTheme({
    palette: {
        mode: isThemeDark ? "dark": "light",
        primary: {
            main: '#6948ff',
            light: '#fff',
            dark: '#4f2ee4',
        },
        secondary: {
            main: isThemeDark ? '#818181' : '#080808',
        },
        background: {
            default: isThemeDark ? "#2f303d" : "#fff",
            paper: isThemeDark ? "#21212C" : "#F6F4FE",
        },
    },
    components: {
        MuiContainer: {
            styleOverrides: {
                root: {
                    paddingLeft: "20px",
                    paddingRight: "20px"
                }
            },
            defaultProps: {
                disableGutters: true
            }
        }
    },
    typography: {
        "fontFamily": `"Helvetica Neue", sans-serif`,
        "fontSize": 14,                
        "fontWeightLight": 300,
        "fontWeightRegular": 400,
        "fontWeightMedium": 500
    }
});