import axios from "axios";

const api = axios.create({
    baseURL: "http://10.9.3.24:5198",
    headers: {
        'Content-Type': "application/json; charset=utf8",
    }
});

export const methods = {
    provider: {
        get() {
            return api.get<Provider[]>('/provider');
        },
        create(data: CreatedProviderParams) {
            return api.post('/provider', data);
        },
        delete(data: DeleteProviderParams) {
            return api.delete(`/provider/${data.name}`);
        }
    },
    service: {
        get() {
            return api.get<Service[]>('/service');
        },
        create(data: CreateServiceParams) {
            return api.post('/service', data);
        },
        delete(data: DeleteServiceParams) {
            return api.delete(`/service/${data.name}`);
        }
    },
    speed: {
        get() {
            return api.get<Speed[]>('/speed');
        },
        create(data: CreateSpeedParams) {
            return api.post('/speed', data);
        },
        delete(data: DeleteSpeedParams) {
            return api.delete('/speed', { data });
        }
    },
    tariff: {
        get() {
            return api.get<Tariff[]>('/tariff');
        },
        create(data: CreateTariffParams) {
            return api.post('/tariff', data);
        },
        update(data: UpdateTariffParams) {
            return api.put(`/tariff`, data);
        },
        delete(data: DeleteTariffParams) {
            return api.delete(`/tariff/${data.name}`);
        }
    },
    tariffService: {
        get() {
            return api.get<TariffService[]>('/tariff/service');
        },
        create(data: CreateTariffServiceParams) {
            return api.post('/tariff/service', data);
        },
        delete(data: DeleteTariffServiceParams) {
            return api.delete('/tariff/service', { data });
        }
    },
    tariffType: {
        get() {
            return api.get<TariffType[]>('/tariff/type');
        },
        create(data: CreateTariffTypeParams) {
            return api.post('/tariff/type', data);
        },
        delete(data: DeleteTariffTypeParams) {
            return api.delete('/tariff/type', { data });
        }
    },
    type: {
        get() {
            return api.get<Type[]>('/type');
        },
        create(data: CreateTypeParams) {
            return api.post('/type', data);
        },
        delete(data: DeleteTypeParams) {
            return api.delete(`/type`, { data });
        }
    }
};