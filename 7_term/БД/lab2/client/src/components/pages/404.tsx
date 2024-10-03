import Box from '@mui/material/Box';
import Button from '@mui/material/Button';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import useMediaQuery from '@mui/material/useMediaQuery';
import type { Theme } from '@mui/material/styles/createTheme';
import { RouterLink } from '../../utilities/RouterLink';
import {Helmet} from "react-helmet";

const Page404 = () => {
    const mdUp = useMediaQuery((theme: Theme) => theme.breakpoints.down('md'));

    return (
        <Box
            sx={{
                alignItems: 'center',
                display: 'flex',
                flexGrow: 1,
                py: '80px',
                height: "calc(100vh - 100px)"
            }}
        >
            <Helmet>
                <title>404</title>
                <meta name="description" content="Page not found"></meta>
            </Helmet>
            <Container maxWidth="lg">
                <Box
                    sx={{
                        display: 'flex',
                        justifyContent: 'center',
                        mb: 6,
                    }}
                >
                    <Typography variant={mdUp ? 'h2': 'h1'} sx={{fontWeight: 700}}>404</Typography>
                </Box>
                <Typography
                    align="center"
                    variant={mdUp ? 'h4' : 'h2'}
                >
                    The page you are looking for isn’t here
                </Typography>
                <Typography
                    align="center"
                    color="text.secondary"
                    sx={{ mt: 0.5 }}
                >
                    You either tried some shady route or you came here by mistake. Whichever it
                    is, try using the navigation.
                </Typography>
                <Box
                    sx={{
                        display: 'flex',
                        justifyContent: 'center',
                        mt: 6,
                    }}
                >
                    <Button
                        component={RouterLink}
                        to={"/"}
                    >
                        Back to Home
                    </Button>
                </Box>
            </Container>
        </Box>
    );
};

export default Page404;