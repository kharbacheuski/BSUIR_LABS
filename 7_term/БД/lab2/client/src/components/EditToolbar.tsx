import { Button} from "@mui/material";
import { 
    GridRowModes, 
    GridRowModesModel,
    GridToolbarContainer,
    GridRowsProp,
    GridToolbarProps
} from '@mui/x-data-grid';
import AddIcon from '@mui/icons-material/Add';
import { randomId } from '@mui/x-data-grid-generator';

export const EditToolbar = (props: GridToolbarProps) => {
    const { setRows, setRowModesModel } = props;
    const id = randomId();

    const handleClick = () => {
        setRows((oldRows) => [
            {   
                id: id,
            },
            ...oldRows
        ]);
        setRowModesModel((oldModel) => ({
            ...oldModel,
            [id]: { mode: GridRowModes.Edit, isNew: true },
        }));
    };

    return (
        <GridToolbarContainer>
            <Button 
                variant="contained"
                color="primary" 
                startIcon={<AddIcon />} 
                onClick={handleClick}
            >
                Create
            </Button>
        </GridToolbarContainer>
    );
}

export default EditToolbar;