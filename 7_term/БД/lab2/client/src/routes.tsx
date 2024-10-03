import { Navigate, useRoutes } from "react-router-dom";
import { FC } from "react";
import Home from "./components/pages/page";
import TypeconfigurationTable from "./components/pages/type/page";
import TariffConfigurationTable from "./components/pages/tariff/page";
import Page404 from "./components/pages/404";
import SpeedConfigurationTable from "./components/pages/speed/page";
import ProviderConfigurationTable from "./components/pages/provider/page";
import ServiceConfigurationTable from "./components/pages/service/page";

export const ProtectedRoute = ({ isAuth, children }) => {
    if (!isAuth) {
        return <Navigate to="/sign-in" />;
    }

    return children;
};

export const Element: FC<{isAuth: boolean}> = ({isAuth}) => {
    const routes = useRoutes([
        {path: '/', element: <ProtectedRoute isAuth={isAuth} children={<Home />} />},
        {path: '/type', element: <ProtectedRoute isAuth={isAuth} children={<TypeconfigurationTable />} />},
        {path: '/tariff', element: <ProtectedRoute isAuth={isAuth} children={<TariffConfigurationTable />} />},
        {path: '/service', element: <ProtectedRoute isAuth={isAuth} children={<ServiceConfigurationTable />} />},
        {path: '/provider', element: <ProtectedRoute isAuth={isAuth} children={<ProviderConfigurationTable />} />},
        {path: '/speed', element: <ProtectedRoute isAuth={isAuth} children={<SpeedConfigurationTable />} />},
        {path: '*', element: <Navigate to="404" />},
        {path: '/404', element: <ProtectedRoute isAuth={isAuth} children={<Page404 />} />},
    ])

    return routes
}