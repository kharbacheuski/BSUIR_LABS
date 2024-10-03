import { AxiosError } from "axios"

export const getAxiosErrorMessage = (error: AxiosError | any) => {
    const message = Object.values(error.response?.data.errors || {}).reduce(
        (acc, curr) => `${acc} ${curr}`, ""
    ) || error.message

    return message
}