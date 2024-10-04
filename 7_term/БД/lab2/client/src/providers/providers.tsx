import ThemeProvider from './theme-provider';
import { Container } from '@mui/material';
import AuthProvider from './auth-provider';

export default function Providers({ children }: { children: React.ReactNode }) {
    return (
        <AuthProvider>
            <ThemeProvider>
                <Container maxWidth="lg">
                    {children}
                </Container>
            </ThemeProvider> 
        </AuthProvider>
    )
}