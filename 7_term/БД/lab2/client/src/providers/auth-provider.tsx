import React, { useEffect, createContext, useState } from 'react';

type AuthContextType = {
    isAuth: boolean,
    setIsAuth: React.Dispatch<React.SetStateAction<boolean>>
}

export const AuthContext = createContext<AuthContextType>({
    isAuth: false,
    setIsAuth: () => {}
})
 
function AuthProvider({ children }) {
    const [isAuth, setIsAuth] = useState<boolean>(true)

    useEffect(() => {
        const time = Number(localStorage.getItem("session")) || 0

        if(time < new Date().getTime()) {
            setIsAuth(false)
        }
    }, [])

    return (
        <AuthContext.Provider value={{isAuth, setIsAuth}}>
            {children}
        </AuthContext.Provider>
    )
}

export default AuthProvider