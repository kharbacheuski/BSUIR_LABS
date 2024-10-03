type Provider = {
    name: string
    popularity: number
    coverage: number
}
type CreatedProviderParams = Provider
type DeleteProviderParams = Pick<Provider, "name">

type Service = {
    name: string
    price: number
    period: number
}
type CreateServiceParams = {
    name: string
    price: number
    periodInDays: number
}
type DeleteServiceParams = Pick<Service, "name">


type Speed = {
    incoming: number
    outgoing: number
}
type CreateSpeedParams = Speed
type DeleteSpeedParams = Speed


type Tariff = {
    name: string
    speed: string
    providerName: string
}
type CreateTariffParams = Pick<Tariff, ["name","providerName"]> & Speed
type UpdateTariffParams = CreateTariffParams
type DeleteTariffParams = Pick<Tariff, "name">


type TariffService = {
    tariffName: string
    serviceName: string
}
type CreateTariffServiceParams = TariffService
type DeleteTariffServiceParams = TariffService

type TariffType = {
    tariffName: string
    typeName: string
}
type CreateTariffTypeParams = TariffType
type DeleteTariffTypeParams = TariffType

type Type = {
    name: string
    isPremium: boolean
    bySale: boolean
}
type CreateTypeParams = Type
type DeleteTypeParams = Type
