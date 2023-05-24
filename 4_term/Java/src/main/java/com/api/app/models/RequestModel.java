package com.api.app.models;

import com.fasterxml.jackson.annotation.JsonProperty;

public class RequestModel {

    @JsonProperty("middleNumber")
    Double middleNumber;

    public void setMiddleNumber(Double val) {
        middleNumber = val;
    }
    public Double getMiddleNumber() {
        return middleNumber;
    }
}
