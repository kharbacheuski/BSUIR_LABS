import { BrowserRouter } from 'react-router-dom';
import "./styles/base.scss"
import { Element } from './routes';
import Providers from './providers/providers';
import Header from './components/header/Header';
import { Box } from '@mui/material';
  
const Main = () => {
    return (
        <BrowserRouter>
            <Providers>
                <Header />

                <Box sx={{marginTop: "80px"}}>
                    <Element />  
                </Box>
            </Providers>         
        </BrowserRouter>
    )
}

export default Main