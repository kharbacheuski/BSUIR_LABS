package com.api.app.models;

public class FilteringInfoModel {
    public String name;

    public double min;

    public double middle;

    public double max;

    public FilteringInfoModel(String _name, double _min, double _mid, double _max) {
        name  = _name;
        min = _min;
        middle = _mid;
        max = _max;
    }
}
