import { Navigate, useRoutes } from "react-router-dom";
import { FC, useContext } from "react";
import Home from "./components/pages/page";
import TypeconfigurationTable from "./components/pages/type/page";
import TariffConfigurationTable from "./components/pages/tariff/page";
import Page404 from "./components/pages/404";
import SpeedConfigurationTable from "./components/pages/speed/page";
import ProviderConfigurationTable from "./components/pages/provider/page";
import ServiceConfigurationTable from "./components/pages/service/page";
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
        {path: '/type', element: <ProtectedRoute isAuth={isAuth} children={<TypeconfigurationTable />} />},
        {path: '/tariff', element: <ProtectedRoute isAuth={isAuth} children={<TariffConfigurationTable />} />},
        {path: '/service', element: <ProtectedRoute isAuth={isAuth} children={<ServiceConfigurationTable />} />},
        {path: '/provider', element: <ProtectedRoute isAuth={isAuth} children={<ProviderConfigurationTable />} />},
        {path: '/speed', element: <ProtectedRoute isAuth={isAuth} children={<SpeedConfigurationTable />} />},
        {path: '*', element: <Navigate to="404" />},
        {path: '/404', element: <ProtectedRoute isAuth={isAuth} children={<Page404 />} />},
        {path: '/sign-in', element: <AuthPage />},
    ])

    return routes
}