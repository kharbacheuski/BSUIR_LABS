package com.api.app.models;

import com.fasterxml.jackson.annotation.JsonProperty;

public class CountRequestsModel {
    @JsonProperty("countOfRequests")
    public int countOfRequests;
}
