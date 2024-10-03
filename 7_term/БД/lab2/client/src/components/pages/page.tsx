import { Box, Typography } from "@mui/material";
import React, { useState, useEffect, memo } from "react";

const Home: React.FC<{}> = ({}) => {
    return (
        <Box>
            <Typography variant="h1">Home</Typography>

            <Typography sx={{marginTop: "50px"}}>Это домашняя страница системы и тут пока ничего нет</Typography>
            <Typography>А может никогда и не будет...</Typography>
        </Box>
    )
}

export default memo(Home)
