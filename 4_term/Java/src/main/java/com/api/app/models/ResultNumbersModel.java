package com.api.app.models;

import com.fasterxml.jackson.annotation.JsonProperty;

public class ResultNumbersModel {
    @JsonProperty("beforeNumber")
    public double beforeNumber;
    @JsonProperty("afterNumber")
    public double afterNumber;

    public ResultNumbersModel(double b, double a) {
        beforeNumber = b;
        afterNumber = a;
    }

    public void setBeforeNumber(double val) {
        beforeNumber = val;
    }

    public void setAfterNumber(double val) {
        afterNumber = val;
    }
}
