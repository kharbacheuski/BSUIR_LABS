import { forwardRef } from "react";
import { Link, NavLink, NavLinkProps, LinkProps } from "react-router-dom";

const style = {
    textDecoration: "none",
    color: "inherit",
    fontSize: "18px",   

    ".active": {
        color: "#fff",
    },

    ":hover": {
        color: "#fff",
        textDecoration: "none"
    }
}

export const RouterLink = forwardRef(function RouterLink(props: LinkProps, ref: any) {
    const { ...other } = props;

    return (
        <Link
            ref={ref}
            {...other}
        />
    );
});