import { CircularProgress } from '@mui/material';
import Box from '@mui/material/Box';

const CustomLoader = ({isLoading}) => {
    return (
        isLoading &&
            <Box sx={{ 
                display: 'flex', 
                position: "fixed", 
                width: "100%", 
                height: "100%", 
                alignItems: "center",
                justifyContent: "center",
                top: "0",
                left: "0",
                backgroundColor: "white",
                opacity: 0.7,
                zIndex: 200
            }}>
                <CircularProgress />
            </Box>
    )
}

export default CustomLoader