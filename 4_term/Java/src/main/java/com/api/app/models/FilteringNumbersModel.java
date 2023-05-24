package com.api.app.models;
import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.ArrayList;

public class FilteringNumbersModel {
    @JsonProperty("results")
    public ArrayList<ResultNumbersModel> results;

    @JsonProperty("filteringInfo")
    public ArrayList<FilteringInfoModel> filteringInfo;

    public FilteringNumbersModel(ArrayList<ResultNumbersModel> _r, ArrayList<FilteringInfoModel> _fi) {
        results = _r;
        filteringInfo = _fi;
    }

}
