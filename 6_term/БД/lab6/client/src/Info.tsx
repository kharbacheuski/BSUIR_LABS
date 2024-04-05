import { Button, Box, Typography, TextField } from "@mui/material"

const Info = () => {
    return <Box>
        <Typography align="center" variant="h2">Info</Typography>

        <Box sx={{display: "flex", gap: "10rem", mt: "5rem"}}>
            <Box >
                <Typography sx={{mb: "1rem"}} variant="h4">Запросы из 4 ЛР</Typography>

                <Box>
                    <Typography>1) where</Typography>
                    <Typography>2) where-orderBy</Typography>
                    <Typography>3) orderBy</Typography>
                    <Typography>4) select</Typography>
                    <Typography>5) select-where</Typography>
                    <Typography>6) crossJoin</Typography>
                    <Typography>7) crossJoin-2</Typography>
                    <Typography>8) innerJoin</Typography>
                    <Typography>9) innerJoin-where</Typography>
                    <Typography>10) leftOuterJoin-where</Typography>
                    <Typography>11) leftOuterJoin</Typography>
                    <Typography>12) rightOuterJoin</Typography>
                    <Typography>13) rightOuterJoin-2</Typography>
                    <Typography>14) fullOuterJoin</Typography>
                    <Typography>15) fullOuterJoin-2</Typography>
                </Box>
            </Box>

            <Box>
                <Typography sx={{mb: "1rem"}} variant="h4">Запросы из 5 ЛР</Typography>

                <Box>
                    <Typography>16) count</Typography>
                    <Typography>17) count-distinct</Typography>
                    <Typography>18) max</Typography>
                    <Typography>19) max-2</Typography>
                    <Typography>20) sum</Typography>
                    <Typography>21) sum-distinct</Typography>
                    <Typography>22) groupBy</Typography>
                    <Typography>23) groupBy-having</Typography>
                    <Typography>24) having-avg</Typography>
                    <Typography>25) union-not</Typography>
                    <Typography>26) union-any</Typography>
                    <Typography>27) intersect</Typography>
                    <Typography>28) intersect-where</Typography>
                    <Typography>29) except-exists</Typography>
                    <Typography>30) except-all</Typography>
                </Box>
            </Box>
        </Box>
    </Box>
}

export default Info