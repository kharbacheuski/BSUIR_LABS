type Genre = {
    name: string
    instruments: string
}
type CreatedGenreParams = Genre
type DeleteGenreParams = Pick<Genre, "name">

type Group = {
    name: string
    personsCount: number
    popularity: number
}
type CreateGroupParams = Group
type DeleteGroupParams = Pick<Group, "name">

type Room = {
    number: string
    square: number
    personsCount: number
    rent: number
}
type CreateRoomParams = Room
type DeleteRoomParams = Pick<Room, "number">


type MusicRecord = {
    number: string
    date: string
    hours: number
    roomNumber: string
    groupName: string
}
type CreateMusicRecordParams = MusicRecord
type DeleteMusicRecordParams = Pick<MusicRecord, "name">


type RecordGenre = {
    recordNumber: string
    genreName: string
}
type CreateRecordGenreParams = RecordGenre
type DeleteRecordGenreParams = RecordGenre

type GroupGenre = {
    groupName: string
    genreName: string
}
type CreateGroupGenreParams = GroupGenre
type DeleteGroupGenreParams = GroupGenre