import React from "react";
import { Button, Box } from "@mui/material";
import { 
    GridRenderEditCellParams, 
    GridRowId,
    GridRowModes
} from '@mui/x-data-grid';
import { AlertStateType, } from "./Alert";
import { methods } from "../api/methods";
import { getAxiosErrorMessage } from "@/utilities/get-axios-error-message";
import { randomId } from "@mui/x-data-grid-generator";

enum RowActions {
    create,
    update,
    delete
}

const Buttons: React.FC<{
    params: GridRenderEditCellParams, 
    isEditing: boolean,
    rows,
    setRows,
    rowModesModel
    setRowModesModel
    setError: (data: AlertStateType) => void,
    setIsLoading,
    apiName: string,
    isEditable?: boolean
}> = ({params, isEditing, rows, setRows, rowModesModel, setRowModesModel, setIsLoading, setError, apiName, isEditable = false}) => {

    const handleDeleteClick = (id: GridRowId) => {
        setRows(rows.filter((row) => row.id !== id));
    };
    const handleEditClick = (id: GridRowId) => {
        setRowModesModel({ ...rowModesModel, [id]: { mode: GridRowModes.Edit } });
    };
    const handleSaveClick = (id: GridRowId) => {
        setRowModesModel({ ...rowModesModel, [id]: { mode: GridRowModes.View } });
    };
    const handleCancelClick = (id: GridRowId) => {
        setRowModesModel({
            ...rowModesModel,
            [id]: { mode: GridRowModes.View, ignoreModifications: true },
        });

        if(rowModesModel[id]?.isNew) 
            handleDeleteClick(id)
    };

    const handleAction = async (type: RowActions, params) => {
        try {
            setIsLoading(true)

            switch(type) {
                case RowActions.update: {
                    handleSaveClick(params.id);

                    await methods[apiName].update(params.row);
                }; break;

                case RowActions.create: {
                    handleSaveClick(params.id);

                    let {data: newRow} = await methods[apiName].create(params.row);

                    handleDeleteClick(params.id)

                    newRow.id = params.id;

                    setRows((prev) => [...prev, newRow]);
                }; break;

                case RowActions.delete: {
                    handleSaveClick(params.id);

                    await methods[apiName].delete(params.row);

                    handleDeleteClick(params.id)
                }; break;
            }
        }
        catch(e) {
            const message = getAxiosErrorMessage(e)

            setError({isOpen: true, message, severity: "error"})
    
            if(rowModesModel[params.id]?.isNew)
                handleDeleteClick(params.id)
        }
        finally {
            setIsLoading(false)
        }
    };

    return (
        <Box sx={{display: "flex", flexDirection: "row", justifyContent: "space-around", alignItems: "center", width: "100%", height: "100%"}}>
            {!isEditable && isEditing && <Button 
                style={{height: "27px", width: "50px", fontSize: "12px"}} 
                variant="contained"
                onClick={() => {
                    isEditing ? handleAction(rowModesModel[params.id]?.isNew ? RowActions.create : RowActions.update, params) : handleEditClick(params.id);
                }}
            >
                {isEditing? rowModesModel[params.id]?.isNew ? "Create" : "Update" : "Edit"}
            </Button>}
            {isEditable && <Button 
                style={{height: "27px", width: "50px", fontSize: "12px"}} 
                variant="contained"
                onClick={() => {
                    isEditing ? handleAction(rowModesModel[params.id]?.isNew ? RowActions.create : RowActions.update, params) : handleEditClick(params.id);
                }}
            >
                {isEditing? rowModesModel[params.id]?.isNew ? "Create" : "Update" : "Edit"}
            </Button>}
            <Button 
                style={{height: "27px", width: "50px", fontSize: "12px"}} 
                color={isEditing ? "secondary" : "error"} 
                variant="contained"
                onClick={() => {
                    isEditing ? handleCancelClick(params.id) : handleAction(RowActions.delete, params)
                }}
            >
                {isEditing ? "Cancel" : "delete"}
            </Button>
        </Box>
    )
}

export default Buttons