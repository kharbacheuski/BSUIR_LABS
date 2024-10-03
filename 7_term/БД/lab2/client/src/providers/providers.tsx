import ThemeProvider from './theme-provider';
import { Suspense } from 'react';
import Loading from "@/components/Loader"
import { Container } from '@mui/material';

export default function Providers({ children }: { children: React.ReactNode }) {
    return (
        <Suspense fallback={<Loading isLoading={true} />}>
            <ThemeProvider>
                <Container maxWidth="lg">
                    {children}
                </Container>
            </ThemeProvider> 
        </Suspense>
    )
}