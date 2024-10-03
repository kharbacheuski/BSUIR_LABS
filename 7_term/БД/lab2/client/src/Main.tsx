import React, { createContext, useState } from 'react';
import { BrowserRouter } from 'react-router-dom';
import "./styles/base.scss"
import { Element } from './routes';
import Providers from './providers/providers';
import Header from './components/header/Header';
  
const Main = () => {
    const [isAuth, setIsAuth] = useState<boolean>(true)

    return (
        <BrowserRouter>
            <Providers>
                <Header />
                <Element isAuth={isAuth} />   
            </Providers>         
        </BrowserRouter>
    )
}

export default Main