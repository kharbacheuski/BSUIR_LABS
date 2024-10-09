import axios from "axios";

const api = axios.create({
    baseURL: "http://localhost:5198/",
    headers: {
        'Content-Type': "application/json; charset=utf8",
    }
});

export const methods = {
    genre: {
        get() {
            return api.get<Genre[]>('/genre');
        },
        create(data: CreatedGenreParams) {
            return api.post('/genre', data);
        },
        delete(data: DeleteGenreParams) {
            return api.delete(`/genre/${data.name}`);
        }
    },
    group: {
        get() {
            return api.get<Group[]>('/group');
        },
        create(data: CreateGroupParams) {
            return api.post('/group', data);
        },
        delete(data: DeleteGroupParams) {
            return api.delete(`/group/${data.name}`);
        }
    },
    groupGenre: {
        get() {
            return api.get<GroupGenre[]>('/group/genre');
        },
        create(data: CreateGroupGenreParams) {
            return api.post('/group/genre', data);
        },
        delete(data: DeleteGroupGenreParams) {
            return api.delete(`/group/genre`, { data });
        }
    },
    record: {
        get() {
            return api.get<MusicRecord[]>('/record');
        },
        create(data: CreateMusicRecordParams) {
            return api.post('/record', data);
        },
        delete(data: DeleteMusicRecordParams) {
            return api.delete('/record', { data });
        }
    },
    recordGenre: {
        get() {
            return api.get<RecordGenre[]>('/record/genre');
        },
        create(data: CreateRecordGenreParams) {
            return api.post('/record/genre', data);
        },
        delete(data: DeleteRecordGenreParams) {
            return api.delete(`/record/genre/`, { data });
        }
    },
    room: {
        get() {
            return api.get<Room[]>('/room');
        },
        create(data: CreateRoomParams) {
            return api.post('/room', data);
        },
        delete(data: DeleteRoomParams) {
            return api.delete(`/room/${data.number}`);
        }
    },
};