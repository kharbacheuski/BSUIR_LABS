import { Alert , AlertTitle , IconButton  } from '@mui/material';
import CloseIcon from '@mui/icons-material/Close';

export type AlertStateType = {
    isOpen: boolean,
    message: string,
    severity: "success" | "info" | "warning" | "error" | undefined
}

const AlertComponent: React.FC<{
    state: AlertStateType, 
    setState: React.Dispatch<React.SetStateAction<AlertStateType>>
}> = ({state, setState}) => {
    return (state.isOpen &&
        <Alert 
            sx={{
                zIndex: 12,
                width: "calc(100% - 45px)",
                position: "fixed",
                bottom: "15px",
                left: "15px"
            }}
            action={
                <IconButton
                    aria-label="close"
                    color="inherit"
                    size="small"
                    onClick={() => {
                        setState({isOpen: false, message: "", severity: undefined});
                    }}
                >
                    <CloseIcon fontSize="inherit" />
                </IconButton>
            }
            severity={state.severity}
        >
            <AlertTitle>{state.severity?.toUpperCase()}</AlertTitle>
            {state.message}
        </Alert>
    );
};

export default AlertComponent;