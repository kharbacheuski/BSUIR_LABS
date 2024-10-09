import { Navigate, useRoutes } from "react-router-dom";
import { FC, useContext } from "react";
import Home from "./components/pages/page";
import Genre from "./components/pages/genre/page";
import Group from "./components/pages/group/page";
import Record from "./components/pages/record/page";
import Room from "./components/pages/room/page";
import Page404 from "./components/pages/404";

import { AuthContext } from "./providers/auth-provider";
import AuthPage from "./components/pages/auth/page";

export const ProtectedRoute = ({ isAuth, children }) => {
    if (!isAuth) {
        return <Navigate to="/sign-in" />;
    }

    return children;
};

export const Element = () => {
    const {isAuth} = useContext(AuthContext)

    const routes = useRoutes([
        {path: '/', element: <ProtectedRoute isAuth={isAuth} children={<Home />} />},
        {path: '/genre', element: <ProtectedRoute isAuth={isAuth} children={<Genre />} />},
        {path: '/group', element: <ProtectedRoute isAuth={isAuth} children={<Group />} />},
        {path: '/record', element: <ProtectedRoute isAuth={isAuth} children={<Record />} />},
        {path: '/room', element: <ProtectedRoute isAuth={isAuth} children={<Room />} />},
        {path: '*', element: <Navigate to="404" />},
        {path: '/404', element: <ProtectedRoute isAuth={isAuth} children={<Page404 />} />},
        {path: '/sign-in', element: <AuthPage />},
    ])

    return routes
}