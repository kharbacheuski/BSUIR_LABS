package com.api.app.models;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Collection;

public class NumbersCollectionModel {
    @JsonProperty("collection")
    public Collection<RequestModel> collection;

    public void setCollection(Collection<RequestModel> _c) {
        collection=_c;
    }
    public Collection<RequestModel> getCollection() {
        return collection;
    }
}
