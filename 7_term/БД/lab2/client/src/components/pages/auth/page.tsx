import { useState, FC, useContext } from "react";
import { Box, Button, TextField, Typography } from "@mui/material";
import { AuthContext } from "@/providers/auth-provider";
import { useNavigate } from "react-router-dom";

const AuthPage: FC = () => {
    const [password, setPassword] = useState("");
    const systemPassword = "152437689";

    const navigate = useNavigate();

    const {setIsAuth} = useContext(AuthContext);

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();

        if(password === systemPassword) {
            setIsAuth(true);
            navigate("/");
            localStorage.setItem("session", JSON.stringify(new Date().getTime() + 60 * 60 * 1000));
        }
    };

    return (
        <Box
            display="flex"
            flexDirection="column"
            alignItems="center"
            justifyContent="center"
            height="100vh"
        >
            <Typography variant="h4" gutterBottom>
                Please enter your password
            </Typography>
            <Box
                component="form"
                onSubmit={handleSubmit}
                sx={{
                    display: "flex",
                    flexDirection: "column",
                    alignItems: "center",
                    width: 300,
                }}
            >
                <TextField
                    label="Password"
                    type="password"
                    variant="outlined"
                    fullWidth
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                    sx={{ marginBottom: 2 }}
                />
                <Button variant="contained" color="primary" type="submit">
                    Submit
                </Button>
            </Box>
        </Box>
    );
};

export default AuthPage;