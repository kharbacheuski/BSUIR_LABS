import React, { useState, useEffect, memo } from "react";
import { 
    DataGrid, 
    GridColDef, 
    GridRenderEditCellParams, 
    GridRowModesModel,
} from '@mui/x-data-grid';
import AlertComponent, { AlertStateType} from "../../Alert";
import Buttons from "../../Buttons";
import { Box, Typography } from "@mui/material";
import {  methods } from "../../../api/methods";
import EditToolbar from "@/components/EditToolbar";

const GroupGenreConfigurationTable: React.FC<{}> = ({}) => {
    const apiName = "groupGenre";

    const [error, setError] = useState<AlertStateType>({
        isOpen: false,
        message: "",
        severity: "error",
    })

    const [rows, setRows] = useState<GroupGenre[]>([]);

    const columns: GridColDef[] = [
        {
            field: 'id',
            headerName: 'Id',
            filterable: false,
            hideable: true,
        },
        {            
            field: 'groupName',
            headerName: 'Group',
            flex: 1,
            editable: true,
        },
        {            
            field: 'genreName',
            headerName: 'Genre',
            flex: 1,
            editable: true,
        },
        {
            field: 'actions',
            headerName: '',
            width: 170,
            editable: true,
            sortable: false,
            filterable: false,
			disableColumnMenu: true,
            disableExport: true,
			cellClassName: 'actions',
            renderCell: (params: GridRenderEditCellParams) => (
                <Buttons 
                    params={params} 
                    isEditing={false} 
                    rowModesModel={rowModesModel}
                    setRowModesModel={setRowModesModel}
                    rows={rows}
                    setRows={setRows}
                    setIsLoading={setIsLoading}
                    setError={setError}
                    apiName={apiName}
                />
            ),
            renderEditCell: (params: GridRenderEditCellParams) => (
                <Buttons 
                    params={params} 
                    isEditing={true} 
                    rowModesModel={rowModesModel}
                    setRowModesModel={setRowModesModel}
                    rows={rows}
                    setRows={setRows}
                    setIsLoading={setIsLoading}
                    setError={setError}
                    apiName={apiName}
                />
            )
        },
    ];

    const [rowModesModel, setRowModesModel] = useState<GridRowModesModel>({});

    const [loading, setIsLoading] = useState<boolean>(false)

    const [paginationModel, setPaginationModel] = useState({
        pageSize: 15,
        page: 0,
    });

    const fetchData = async () => {
        try {
            setIsLoading(true);
            const data = (await methods[apiName].get()).data;

            setRows(data.map((row) => ({...row, id: row.genreName + row.groupName})));
        }
        catch(e) {
            console.error(e)
        }
        finally {
            setIsLoading(false);
        };
    };

    useEffect(() => {
        fetchData();
    }, [])
      
    return (
        <Box>
            <Typography sx={{ marginBottom: "20px"}} variant="h2">Группа/Жанр</Typography>

            <Typography sx={{ marginBottom: "20px", maxWidth: "800px"}}>
                На этой странице представлены все жанры, в которых играет группа
            </Typography>

            <DataGrid 
                autoHeight
                pagination
                paginationModel={paginationModel}
                onPaginationModelChange={setPaginationModel}
                pageSizeOptions={[15, 25, 50, 100]}

                rows={rows}
                columns={columns}
                columnVisibilityModel={{
                    id: false
                }}
                disableRowSelectionOnClick
                showCellVerticalBorder
                editMode="row"
                rowModesModel={rowModesModel}
                loading={loading}
                slots={{
                    toolbar: EditToolbar,
                }}
                slotProps={{
                    toolbar: { setRows, setRowModesModel }
                }}
            />

            <Typography variant="caption" sx={{ marginTop: "10px", maxWidth: "800px", fontStyle: "italic"}}>
                Вы можете добавить новую конфигурацию или удалить старую
            </Typography>

            <AlertComponent 
                state={error}
                setState={setError}
            />
        </Box>
    )
}

export default memo(GroupGenreConfigurationTable)
